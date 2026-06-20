#include <bits/stdc++.h>
#include <cstring>
#include <stdexcept>
#include "main.h"
struct point;
// using namespace std;
#define YXDZ "127.0.0.1"
//API开始-----------------------------------------------API开始----------------------------------------------------API开始
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
	APIClient(const std::string &host, int port) {
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
		if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
			close();
			throw std::runtime_error("Connection failed");
		}
	}

	~APIClient() {
		close();
	}

	void
	close() {
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

	std::string
	setColor(int x, int y, const std::string &color) {
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

	std::string
	getColors() {
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

//工具函数申明开始------------------------------------工具函数申明开始-------------------------------------------工具函数申明开始

//结构体开始--------------------------------------------结构体开始--------------------------------------------------结构体开始
struct fs { //表示a/b
	int a, b;

	fs(int x, int y) : a(x), b(y) {
		if (a < 0 && b < 0) a = -a, b = -b;
		if (a > 0 && b < 0) a = -a, b = -b;
		a /= abs(gcd_(x, y));
		b /= abs(gcd_(x, y));
	}
};

fs operator+(const fs &x, const fs &y) {
	int cnt = lcm_(x.b, y.b);
	fs d_x = {x.a * (cnt / x.b), cnt}, d_y = {y.a * (cnt / y.b), cnt};
	return fs(d_x.a + d_y.a, cnt);
}

fs operator-(const fs &x, const fs &y) {
	int cnt = lcm_(x.b, y.b);
	fs d_x = {x.a * (cnt / x.b), cnt}, d_y = {y.a * (cnt / y.b), cnt};
	return fs(d_x.a - d_y.a, cnt);
}

fs operator*(const fs &x, const fs &y) {
	return fs(x.a * y.a, x.b * y.b);
}
fs operator*(const fs &x, const int &y) {
	return fs(x.a * y, x.b);
}
fs operator*(const int &x, const fs &y) {
	return fs(y.a * x, y.b);
}

fs operator/(const fs &x, const fs &y) {
	fs ttmp = fs(y.b, y.a);
	fs temp = x*ttmp;
	return fs(temp.a, temp.b);
}

struct point {
	std::string name;
	fs x, y;
	std::string k;
	// point(std::string s,int a,int b,std::string c):name(s),x(a),y(b),k(c){}
};

struct jxs {
	std::string s;
	fs k, b;
};

struct line {
	std::string name;
	point d_x, d_y;
	jxs s;
	std::string o;
	// line(std::string s,point a,point b,jxs x,std::string p):name(s),d_x(a),d_y(b),s(x),o(p){}
};

//工具函数开始-----------------------------------------工具函数开始------------------------------------------------工具函数开始
jxs point_jxs(const point &d1, const point &d2) {
	fs temp1 = d1.y - d2.y, temp2 = d1.x - d2.x;
	fs k = temp1 / temp2;
	fs b = d1.y - k * d1.x;
	return {"", k, b};
}

void gz() {
	for (int i = 0; i <= 1598; i++) {
		APIClient client("127.0.0.1", 3002);
		client.setColor(400, i, "#000000");
	}
	for (int i = 0; i <= 798; i++) {
		APIClient client("127.0.0.1", 3002);
		client.setColor(i, 800, "#000000");
	}
	APIClient client("127.0.0.1", 3002);
	client.setColor(1, 799, "#000000");
	APIClient client1("127.0.0.1", 3002);
	client1.setColor(2, 798, "#000000");
	APIClient client2("127.0.0.1", 3002);
	client2.setColor(3, 797, "#000000");
	APIClient client3("127.0.0.1", 3002);
	client3.setColor(4, 796, "#000000");
	APIClient client4("127.0.0.1", 3002);
	client4.setColor(5, 795, "#000000");
	APIClient client5("127.0.0.1", 3002);
	client5.setColor(1, 801, "#000000");
	APIClient client6("127.0.0.1", 3002);
	client6.setColor(2, 802, "#000000");
	APIClient client7("127.0.0.1", 3002);
	client7.setColor(3, 803, "#000000");
	APIClient client8("127.0.0.1", 3002);
	client8.setColor(4, 804, "#000000");
	APIClient client9("127.0.0.1", 3002);
	client9.setColor(5, 805, "#000000");

	APIClient client10("127.0.0.1", 3002);
	client10.setColor(399, 1597, "#000000");
	APIClient client11("127.0.0.1", 3002);
	client11.setColor(398, 1596, "#000000");
	APIClient client12("127.0.0.1", 3002);
	client12.setColor(397, 1595, "#000000");
	APIClient client13("127.0.0.1", 3002);
	client13.setColor(396, 1594, "#000000");
	APIClient client14("127.0.0.1", 3002);
	client14.setColor(395, 1593, "#000000");
	APIClient client15("127.0.0.1", 3002);
	client15.setColor(401, 1597, "#000000");
	APIClient client16("127.0.0.1", 3002);
	client16.setColor(402, 1596, "#000000");
	APIClient client17("127.0.0.1", 3002);
	client17.setColor(403, 1595, "#000000");
	APIClient client18("127.0.0.1", 3002);
	client18.setColor(404, 1594, "#000000");
	APIClient client19("127.0.0.1", 3002);
	client19.setColor(405, 1593, "#000000");
}

int jxs_y(const jxs &q, int x) {
	x -= 800;
	const fs temp = q.k * x + q.b;
	return temp.a / temp.b + 400;
}

void g_line(const line &q) {
	for (int i = 0; i <= 1598; i++) {
		APIClient client("127.0.0.1", 3002);
		client.setColor(jxs_y(q.s, i), i, q.o);
	}
}

//对象组开始--------------------------------------------对象组开始--------------------------------------------------对象组开始
std::map<std::string, point> points;
std::map<std::string, line> lines;
//主函数开始--------------------------------------------主函数开始--------------------------------------------------主函数开始
int main() {
//	fs a1 = {-2, 1}, a2 = {-2, 1};
//	fs b7 = a1 / a2;
	gz();
	while (true) {
		std::string cz;
		std::cin >> cz;
		if (cz == "new") {
			std::string cz1;
			std::cin >> cz1;
			if (cz1 == "point") { //创建点
				int x, y;
				std::string name, k;
				std::cin >> name >> x >> y >> k;
				if (jc(x, y)) { //在坐标系中
					if (points.find(name) == points.end()) { //未重名
						point o = {name, fs(x, 1), fs(y, 1), k};
						points.insert({name, o}); //加入点集合
					}
					APIClient client(YXDZ, 3002); //发送给前端
					client.setColor(x, y, k);
				}
			} else if (cz1 == "line-d") { //创建直线-两点
				std::string name, name1, name2, k; //解析式名字，点1名字，点2名字，颜色
				std::cin >> name >> name1 >> name2 >> k;
				if (points.find(name1) != points.end() && points.find(name2) != points.end() && lines.find(name) ==
				    lines.
				    end()) { //两点存在且直线不存在
					// 使用 at() 避免触发 map::operator[] 对默认构造的需求
					point p1 = points.at(name1);
					point p2 = points.at(name2);
					p1.x = p1.x - fs(400, 1), p1.y = p1.y - fs(800, 1), p2.x = p2.x - fs(400, 1), p2.y =
					                                     p2.y - fs(800, 1);
					jxs o = point_jxs(p1, p2); //解析式
					line s = {name, p1, p2, o, k}; //直线
					lines.insert({name, s});
					g_line(s);
				}
			}
		}
	}
}

