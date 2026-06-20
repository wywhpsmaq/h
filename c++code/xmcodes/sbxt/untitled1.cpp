#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

#include <winsock2.h>
#include <windows.h>

// #pragma comment(lib, "ws2_32.lib")

// ------------------------------------------------------------
// 1. 矩阵转 JSON（手动拼接）
// ------------------------------------------------------------
std::string matrixToJson(const std::vector<std::vector<int>>& matrix) {
	std::ostringstream oss;
	oss << "{\"matrix\":[";

	for (size_t i = 0; i < matrix.size(); ++i) {
		oss << "[";
		for (size_t j = 0; j < matrix[i].size(); ++j) {
			oss << matrix[i][j];
			if (j != matrix[i].size() - 1) oss << ",";
		}
		oss << "]";
		if (i != matrix.size() - 1) oss << ",";
	}
	oss << "]}";
	return oss.str();
}

// ------------------------------------------------------------
// 2. 发送 HTTP POST 请求（修正二进制数据接收）
// ------------------------------------------------------------
std::string httpPost(const std::string& host, int port, const std::string& path, const std::string& body) {
	WSADATA wsaData;
	SOCKET sock = INVALID_SOCKET;
	std::string response;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup 失败" << std::endl;
		return "";
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "socket 创建失败，错误码: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return "";
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(host.c_str());

	if (connect(sock, (struct sockaddr * )&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cerr << "连接失败，错误码: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return "";
	}

	// 构造请求
	std::ostringstream requestStream;
	requestStream << "POST " << path << " HTTP/1.1\r\n";
	requestStream << "Host: " << host << "\r\n";
	requestStream << "Content-Type: application/json\r\n";
	requestStream << "Content-Length: " << body.size() << "\r\n";
	requestStream << "Connection: close\r\n";
	requestStream << "\r\n";
	requestStream << body;

	std::string request = requestStream.str();

	if (send(sock, request.c_str(), (int)request.size(), 0) == SOCKET_ERROR) {
		std::cerr << "发送失败，错误码: " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return "";
	}

	// 接收数据（修正：使用 append(buffer, bytesReceived) 防止二进制截断）
	char buffer[8192];
	int bytesReceived;
	while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
		response.append(buffer, bytesReceived);
	}

	if (bytesReceived == SOCKET_ERROR) {
		std::cerr << "接收数据时出错，错误码: " << WSAGetLastError() << std::endl;
	}

	closesocket(sock);
	WSACleanup();
	return response;
}

// ------------------------------------------------------------
// 3. 从 HTTP 响应中提取正文（支持 Content-Length 和 chunked）
// ------------------------------------------------------------
bool extractBody(const std::string& httpResponse, std::string& body) {
	size_t headerEnd = httpResponse.find("\r\n\r\n");
	if (headerEnd == std::string::npos) {
		std::cerr << "无效的 HTTP 响应：未找到头部结束标记" << std::endl;
		return false;
	}

	std::string headers = httpResponse.substr(0, headerEnd);
	std::string rawBody = httpResponse.substr(headerEnd + 4);

	// 检测 Content-Length
	std::regex contentLengthRegex("Content-Length: (\\d+)", std::regex::icase);
	std::smatch match;
	long long contentLength = -1;
	if (std::regex_search(headers, match, contentLengthRegex) && match.size() > 1) {
		contentLength = std::stoll(match[1]);
	}

	// 检测 chunked
	bool isChunked = headers.find("Transfer-Encoding: chunked") != std::string::npos;

	if (!isChunked && contentLength >= 0) {
		if (rawBody.size() >= (size_t)contentLength) {
			body = rawBody.substr(0, (size_t)contentLength);
			return true;
		} else {
			std::cerr << "警告：实际接收数据 (" << rawBody.size()
			          << " 字节) 小于 Content-Length (" << contentLength
			          << " 字节)，请检查网络或服务器" << std::endl;
			// 仍然保存已接收部分（可能图片不完整）
			body = rawBody;
			return false;
		}
	} else if (isChunked) {
		// 简单解码 chunked（略，一般情况下后端不使用）
		std::string decoded;
		size_t pos = 0;
		while (pos < rawBody.size()) {
			size_t lineEnd = rawBody.find("\r\n", pos);
			if (lineEnd == std::string::npos) break;
			std::string chunkSizeStr = rawBody.substr(pos, lineEnd - pos);
			chunkSizeStr.erase(std::remove_if(chunkSizeStr.begin(), chunkSizeStr.end(), ::isspace), chunkSizeStr.end());
			if (chunkSizeStr.empty()) break;
			size_t chunkSize = std::stoul(chunkSizeStr, nullptr, 16);
			pos = lineEnd + 2;
			if (chunkSize == 0) break;
			if (pos + chunkSize > rawBody.size()) break;
			decoded += rawBody.substr(pos, chunkSize);
			pos += chunkSize;
			if (pos + 2 <= rawBody.size() && rawBody.substr(pos, 2) == "\r\n") {
				pos += 2;
			}
		}
		body = decoded;
		return true;
	} else {
		// 无 Content-Length，直接返回全部
		body = rawBody;
		return true;
	}
}

// ------------------------------------------------------------
// 4. 核心函数：传入矩阵，生成并保存图片
// ------------------------------------------------------------
bool generateImageFromMatrix(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
	if (matrix.size() != 50) {
		std::cerr << "错误：矩阵行数不是 50（实际为 " << matrix.size() << "）" << std::endl;
		return false;
	}
	for (const auto& row : matrix) {
		if (row.size() != 50) {
			std::cerr << "错误：矩阵列数不是 50（实际为 " << row.size() << "）" << std::endl;
			return false;
		}
	}

	std::string jsonBody = matrixToJson(matrix);
	std::string response = httpPost("127.0.0.1", 3001, "/api/generate", jsonBody);
	if (response.empty()) {
		std::cerr << "HTTP 请求失败或响应为空" << std::endl;
		return false;
	}

	// 可选：打印响应头（调试用）
	size_t headerEnd = response.find("\r\n\r\n");
	if (headerEnd != std::string::npos) {
		std::cout << "=== 响应头部 ===\n" << response.substr(0, headerEnd) << "\n================" << std::endl;
	}

	std::string imageData;
	bool success = extractBody(response, imageData);
	if (imageData.empty()) {
		std::cerr << "提取的图片数据为空" << std::endl;
		return false;
	}

	// 写入文件
	std::ofstream outFile(filename, std::ios::binary);
	if (!outFile) {
		std::cerr << "无法创建文件: " << filename << std::endl;
		return false;
	}
	outFile.write(imageData.data(), imageData.size());
	outFile.close();

	std::cout << "图片已保存到 " << filename << "，大小: " << imageData.size() << " 字节" << std::endl;
	return success;  // 即使数据不完整，也返回 true 让用户检查
}

// ------------------------------------------------------------
// 5. 主函数
// ------------------------------------------------------------
int main() {
	// 生成 50x50 棋盘格矩阵
	std::vector<std::vector<int>> matrix(50, std::vector<int>(50, 0));
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			matrix[i][j] = (i + j) % 2;
		}
	}

	if (generateImageFromMatrix(matrix, "output.png")) {
		std::cout << "处理完成，请检查 output.png 是否正常" << std::endl;
	} else {
		std::cerr << "生成图片失败" << std::endl;
	}

	return 0;
}
