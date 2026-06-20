//
// Created by wywhpsmaq on 2026/1/23.
//

#ifndef H_CS_H
#define H_CS_H

#endif //H_CS_H



#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

class APIClient {
private:
#ifdef _WIN32
    SOCKET sockfd;
#else
    int sockfd;
#endif
    struct sockaddr_in server_addr;

public:
    APIClient(const std::string& host, int port) {
#ifdef _WIN32
        // 初始化Winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup failed");
        }

        // 创建套接字
        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
        // 创建套接字
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
#endif

        if (sockfd < 0) {
            throw std::runtime_error("Failed to create socket");
        }

        // 设置服务器地址
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        // 解析主机地址
        if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
            close();
            throw std::runtime_error("Invalid address/ Address not supported");
        }

        // 连接服务器
        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            close();
            throw std::runtime_error("Connection failed");
        }
    }

    ~APIClient() {
        close();
    }

    void close() {
#ifdef _WIN32
        if (sockfd != INVALID_SOCKET) {
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
        }
        WSACleanup();
#else
        if (sockfd >= 0) {
            ::close(sockfd);
            sockfd = -1;
        }
#endif
    }

    std::string setColor(int x, int y, const std::string& color) {
        // 构建JSON数据
        std::string json_data = "{\"x\":" + std::to_string(x) +
                                ",\"y\":" + std::to_string(y) +
                                ",\"k\":\"" + color + "\"}";

        // 构建HTTP请求
        std::string request = "POST /api/setColor HTTP/1.1\r\n";
        request += "Host: localhost:3002\r\n";
        request += "Content-Type: application/json\r\n";
        request += "Content-Length: " + std::to_string(json_data.size()) + "\r\n";
        request += "Connection: close\r\n\r\n";
        request += json_data;

        // 发送请求
#ifdef _WIN32
        send(sockfd, request.c_str(), request.size(), 0);
#else
        send(sockfd, request.c_str(), request.size(), 0);
#endif

        // 接收响应
        char buffer[4096];
        std::string response;
        int bytes_read;

#ifdef _WIN32
        while ((bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
#else
        while ((bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
#endif
            buffer[bytes_read] = '\0';
            response += buffer;
        }

        return response;
    }

    std::string getColors() {
        // 构建HTTP请求
        std::string request = "GET /api/getColors HTTP/1.1\r\n";
        request += "Host: localhost:3002\r\n";
        request += "Connection: close\r\n\r\n";

        // 发送请求
#ifdef _WIN32
        send(sockfd, request.c_str(), request.size(), 0);
#else
        send(sockfd, request.c_str(), request.size(), 0);
#endif

        // 接收响应
        char buffer[4096];
        std::string response;
        int bytes_read;

#ifdef _WIN32
        while ((bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
#else
        while ((bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
#endif
            buffer[bytes_read] = '\0';
            response += buffer;
        }

        return response;
    }
};