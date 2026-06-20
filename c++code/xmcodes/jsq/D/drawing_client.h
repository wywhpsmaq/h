#ifndef DRAWING_CLIENT_H
#define DRAWING_CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "config.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#endif

class DrawingClient {
#ifdef _WIN32
    SOCKET sockfd = INVALID_SOCKET;
#else
    int sockfd = -1;
#endif
    std::string host;
    int port;

    void cleanup() {
#ifdef _WIN32
        if (sockfd != INVALID_SOCKET) {
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
        }
        WSACleanup();
#else
        if (sockfd >= 0) {
            close(sockfd);
            sockfd = -1;
        }
#endif
    }

    void reconnect() {
        cleanup();
        connect();
    }

    void connect() {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { throw std::runtime_error("WSAStartup failed"); }

        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sockfd == INVALID_SOCKET) {
            WSACleanup();
            throw std::runtime_error("Failed to create socket");
        }
#else
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) { throw std::runtime_error("Failed to create socket"); }
#endif

        sockaddr_in server_addr = {};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
            cleanup();
            throw std::runtime_error("Invalid address");
        }

        // 设置连接超时
#ifdef _WIN32
        constexpr int timeout = 3000; // 3秒
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));
        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char *>(&timeout), sizeof(timeout));
#endif

        if (::connect(sockfd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0) {
            cleanup();
            throw std::runtime_error("Connection failed");
        }
    }

    std::string sendRequest(const std::string &request) {
        if (sockfd < 0) { reconnect(); }

        // 发送请求
        if (const int bytes_sent = send(sockfd, request.c_str(), request.size(), 0); bytes_sent < 0) { throw std::runtime_error("Failed to send request"); }

        // 接收响应
        std::string response;
        char buffer[4096];

        while (true) {
            if (const int bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0); bytes_read > 0) {
                buffer[bytes_read] = '\0';
                response += buffer;
            } else { break; }
        }

        return response;
    }

public:
    explicit DrawingClient(const std::string &host_ = SERVER_HOST, const int port_ = SERVER_PORT) : host(host_), port(port_) { connect(); }

    ~DrawingClient() { cleanup(); }

    // 单个点绘图
    void drawPoint(const int x, const int y, const std::string &color) {
        if (x < 0 || x >= CANVAS_WIDTH || y < 0 || y >= CANVAS_HEIGHT) { throw std::out_of_range("Coordinates out of canvas bounds"); }

        const std::string json_data = "{\"x\":" + std::to_string(x) +
                                ",\"y\":" + std::to_string(y) +
                                ",\"k\":\"" + color + "\"}";

        const std::string request = "POST /api/setColor HTTP/1.1\r\n"
                              "Host: " + host + ":" + std::to_string(port) + "\r\n"
                              "Content-Type: application/json\r\n"
                              "Content-Length: " + std::to_string(json_data.size()) + "\r\n"
                              "Connection: keep-alive\r\n\r\n" +
                              json_data;

        sendRequest(request);
    }

    // 批量绘图
    void drawPoints(const std::vector<std::tuple<int, int, std::string> > &points) {
        if (points.empty()) return;

        // 构建批量JSON
        std::string json_data = "{\"points\":[";
        for (size_t i = 0; i < points.size(); ++i) {
            auto [x, y, color] = points[i];
            json_data += "{\"x\":" + std::to_string(x) +
                    ",\"y\":" + std::to_string(y) +
                    ",\"k\":\"" + color + "\"}";
            if (i < points.size() - 1) json_data += ",";
        }
        json_data += "]}";

        const std::string request = "POST /api/setColors HTTP/1.1\r\n"
                              "Host: " + host + ":" + std::to_string(port) + "\r\n"
                              "Content-Type: application/json\r\n"
                              "Content-Length: " + std::to_string(json_data.size()) + "\r\n"
                              "Connection: keep-alive\r\n\r\n" +
                              json_data;

        sendRequest(request);
    }

    // 获取画布状态
    std::string getCanvasState() {
        const std::string request = "GET /api/getColors HTTP/1.1\r\n"
                              "Host: " + host + ":" + std::to_string(port) + "\r\n"
                              "Connection: keep-alive\r\n\r\n";

        return sendRequest(request);
    }

    // 清空画布
    void clearCanvas(const std::string &color = "#FFFFFF") {
        for (int y = 0; y < CANVAS_HEIGHT; ++y) { for (int x = 0; x < CANVAS_WIDTH; ++x) { drawPoint(x, y, color); } }
    }
};

#endif // DRAWING_CLIENT_H
