#include <bits/stdc++.h>
//#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>
using namespace std;

// 游戏配置
const int MAX_SIZE = 50;
const int MIN_SIZE = 15;
const int MAX_DIFFICULTY = 3;

// 全局变量
int n, m; // 迷宫大小
int difficulty = 2; // 默认难度：1=简单, 2=中等, 3=困难
int startX, startY, endX, endY; // 起点和终点
char maze[MAX_SIZE][MAX_SIZE]; // 迷宫地图
char playerPath[MAX_SIZE][MAX_SIZE]; // 玩家走过的路径
bool visited[MAX_SIZE][MAX_SIZE]; // DFS访问标记
int moveCount = 0; // 移动步数
time_t startTime; // 开始时间

// 方向数组
const int dx[] = {0, -1, 0, 1}; // 上下左右
const int dy[] = {-1, 0, 1, 0};

// 颜色定义
const string COLOR_WALL = "\033[31m"; // 墙 - 红色
const string COLOR_PATH = "\033[32m"; // 路径 - 绿色
const string COLOR_PLAYER = "\033[33m"; // 玩家 - 黄色
const string COLOR_END = "\033[34m"; // 终点 - 蓝色
const string COLOR_VISITED = "\033[36m"; // 走过的路径 - 青色
const string COLOR_RESET = "\033[0m"; // 重置颜色

// 保存终端设置
termios oldt;

// 设置终端为非阻塞模式
void setNonBlockingMode() {
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

// 恢复终端设置
void restoreTerminal() { tcsetattr(STDIN_FILENO, TCSANOW, &oldt); }

// 清除屏幕
void clearScreen() { cout << "\033[2J\033[1;1H"; }

// 检查键盘输入
int kbhit() {
	int bytesWaiting;
	ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
	return bytesWaiting > 0;
}

// 获取键盘输入
char getch() {
	char ch;
	read(STDIN_FILENO, &ch, 1);
	return ch;
}

// 显示游戏菜单
void showMenu() {
	clearScreen();
	cout << "=======================" << endl;
	cout << "      走迷宫游戏      " << endl;
	cout << "=======================" << endl;
	cout << "1. 开始游戏" << endl;
	cout << "2. 设置难度" << endl;
	cout << "3. 游戏说明" << endl;
	cout << "4. 退出游戏" << endl;
	cout << "=======================" << endl;
	cout << "请选择: ";
}

// 设置难度
void setDifficulty() {
	clearScreen();
	cout << "=======================" << endl;
	cout << "      设置难度        " << endl;
	cout << "=======================" << endl;
	cout << "1. 简单 (小迷宫，简单路径)" << endl;
	cout << "2. 中等 (中等迷宫，复杂路径)" << endl;
	cout << "3. 困难 (大迷宫，复杂路径)" << endl;
	cout << "=======================" << endl;
	cout << "当前难度: " << (difficulty == 1 ? "简单" : (difficulty == 2 ? "中等" : "困难")) << endl;
	cout << "请选择难度 (1-3): ";

	char c = getch();
	if (c >= '1' && c <= '3') {
		difficulty = c - '0';
		cout << "\n难度已设置为" << (difficulty == 1 ? "简单" : (difficulty == 2 ? "中等" : "困难")) << endl;
	}
	else { cout << "\n无效选择，保持当前难度" << endl; }
	sleep(1);
}

// 游戏说明
void showInstructions() {
	clearScreen();
	cout << "=======================" << endl;
	cout << "      游戏说明        " << endl;
	cout << "=======================" << endl;
	cout << "使用方向键控制玩家移动" << endl;
	cout << "红色: 墙" << endl;
	cout << "绿色: 可走路径" << endl;
	cout << "黄色: 玩家位置" << endl;
	cout << "蓝色: 终点" << endl;
	cout << "青色: 走过的路径" << endl;
	cout << "目标: 从起点到达终点" << endl;
	cout << "=======================" << endl;
	cout << "按任意键返回菜单...";
	getch();
}

// 生成迷宫尺寸
void generateMazeSize() {
	random_device rd;
	mt19937 gen(rd());

	switch (difficulty) {
	case 1: // 简单
		n = uniform_int_distribution<>(MIN_SIZE, MIN_SIZE + 10)(gen);
		m = uniform_int_distribution<>(MIN_SIZE, MIN_SIZE + 10)(gen);
		break;
	case 2: // 中等
		n = uniform_int_distribution<>(MIN_SIZE + 5, MIN_SIZE + 20)(gen);
		m = uniform_int_distribution<>(MIN_SIZE + 5, MIN_SIZE + 20)(gen);
		break;
	case 3: // 困难
		n = uniform_int_distribution<>(MIN_SIZE + 10, MAX_SIZE)(gen);
		m = uniform_int_distribution<>(MIN_SIZE + 10, MAX_SIZE)(gen);
		break;
	}

	// 确保是奇数，便于迷宫生成
	if (n % 2 == 0) n++;
	if (m % 2 == 0) m++;
}

// 初始化迷宫
void initializeMaze() {
	// 初始化迷宫为墙
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			maze[i][j] = '#'; // #表示墙
			playerPath[i][j] = ' ';
			visited[i][j] = false;
		}
	}
}

// 递归回溯法生成迷宫
void generateMazeDFS(int x, int y) {
	visited[x][y] = true;
	maze[x][y] = ' '; // 标记为路径

	// 随机打乱方向
	vector<int> dirs = {0, 1, 2, 3};
	random_shuffle(dirs.begin(), dirs.end());

	for (int d : dirs) {
		int nx = x + dx[d] * 2;
		int ny = y + dy[d] * 2;

		if (nx >= 1 && nx < n - 1 && ny >= 1 && ny < m - 1 && !visited[nx][ny]) {
			// 打通中间的墙
			maze[x + dx[d]][y + dy[d]] = ' ';
			generateMazeDFS(nx, ny);
		}
	}
}

// 增加迷宫复杂度（添加额外的墙和路径）
void increaseComplexity() {
	random_device rd;
	mt19937 gen(rd());
	int complexityFactor = 0;

	switch (difficulty) {
	case 1:
		complexityFactor = 5;
		break;
	case 2:
		complexityFactor = 10;
		break;
	case 3:
		complexityFactor = 15;
		break;
	}

	// 添加一些随机墙
	for (int i = 0; i < complexityFactor; i++) {
		int x = uniform_int_distribution<>(1, n - 2)(gen);
		int y = uniform_int_distribution<>(1, m - 2)(gen);

		// 确保不是起点或终点附近
		if ((abs(x - startX) > 2 || abs(y - startY) > 2) &&
			(abs(x - endX) > 2 || abs(y - endY) > 2)) { maze[x][y] = '#'; }
	}

	// 添加一些随机路径
	for (int i = 0; i < complexityFactor / 2; i++) {
		int x = uniform_int_distribution<>(1, n - 2)(gen);
		int y = uniform_int_distribution<>(1, m - 2)(gen);

		if (maze[x][y] == '#') { maze[x][y] = ' '; }
	}
}

// 生成起点和终点
void generateStartEnd() {
	random_device rd;
	mt19937 gen(rd());

	// 起点在左上角区域
	startX = uniform_int_distribution<>(1, n / 4)(gen);
	startY = uniform_int_distribution<>(1, m / 4)(gen);

	// 终点在右下角区域
	endX = uniform_int_distribution<>(n * 3 / 4, n - 2)(gen);
	endY = uniform_int_distribution<>(m * 3 / 4, m - 2)(gen);

	// 确保起点和终点是路径
	maze[startX][startY] = ' ';
	maze[endX][endY] = ' ';
}

// 绘制迷宫
void drawMaze(int playerX, int playerY) {
	clearScreen();

	// 绘制顶部边界
	cout << COLOR_WALL;
	for (int j = 0; j < m + 2; j++) { cout << "##"; }
	cout << COLOR_RESET << endl;

	for (int i = 0; i < n; i++) {
		cout << COLOR_WALL << "##" << COLOR_RESET; // 左边界

		for (int j = 0; j < m; j++) {
			if (i == playerX && j == playerY) {
				cout << COLOR_PLAYER << "● " << COLOR_RESET; // 玩家
			}
			else if (i == endX && j == endY) {
				cout << COLOR_END << "★ " << COLOR_RESET; // 终点
			}
			else if (playerPath[i][j] == '*') {
				cout << COLOR_VISITED << "· " << COLOR_RESET; // 走过的路径
			}
			else if (maze[i][j] == '#') {
				cout << COLOR_WALL << "■ " << COLOR_RESET; // 墙
			}
			else {
				cout << COLOR_PATH << "  " << COLOR_RESET; // 路径
			}
		}

		cout << COLOR_WALL << "##" << COLOR_RESET << endl; // 右边界
	}

	// 绘制底部边界
	cout << COLOR_WALL;
	for (int j = 0; j < m + 2; j++) { cout << "##"; }
	cout << COLOR_RESET << endl;

	// 显示游戏信息
	cout << endl;
	cout << "难度: " << (difficulty == 1 ? "简单" : (difficulty == 2 ? "中等" : "困难")) << " | ";
	cout << "迷宫大小: " << n << "x" << m << " | ";
	cout << "步数: " << moveCount << " | ";

	time_t currentTime = time(0);
	int elapsedTime = difftime(currentTime, startTime);
	cout << "时间: " << elapsedTime << "秒" << endl;

	cout << "方向键移动，ESC退出游戏" << endl;
}

// 检查是否到达终点
bool checkWin(int x, int y) { return (x == endX && y == endY); }

// 游戏主循环
void gameLoop() {
	int playerX = startX;
	int playerY = startY;
	moveCount = 0;
	startTime = time(0);

	// 记录起点为已访问
	playerPath[playerX][playerY] = '*';

	while (true) {
		drawMaze(playerX, playerY);

		if (checkWin(playerX, playerY)) {
			clearScreen();
			cout << "=======================" << endl;
			cout << "        恭喜通关！        " << endl;
			cout << "=======================" << endl;
			cout << "迷宫大小: " << n << "x" << m << endl;
			cout << "难度: " << (difficulty == 1 ? "简单" : (difficulty == 2 ? "中等" : "困难")) << endl;
			cout << "移动步数: " << moveCount << endl;
			cout << "用时: " << difftime(time(0), startTime) << "秒" << endl;
			cout << "=======================" << endl;
			cout << "按任意键返回菜单...";
			getch();
			return;
		}

		// 等待键盘输入
		while (!kbhit()) {
			// 可以添加一些动画效果
			usleep(100000);
		}

		char key = getch();
		if (key == 27) { // ESC键退出
			return;
		}

		// 处理方向键（方向键是转义序列）
		if (key == '\033') { // 方向键的第一个字符是ESC
			if (kbhit()) {
				char bracket = getch(); // 第二个字符是'['
				if (bracket == '[') {
					if (kbhit()) {
						char arrow = getch(); // 第三个字符是方向
						int newX = playerX;
						int newY = playerY;

						switch (arrow) {
						case 'A':
							newX--;
							break; // 上
						case 'B':
							newX++;
							break; // 下
						case 'D':
							newY--;
							break; // 左
						case 'C':
							newY++;
							break; // 右
						}

						// 检查是否可以移动
						if (newX >= 0 && newX < n && newY >= 0 && newY < m && maze[newX][newY] != '#') {
							playerX = newX;
							playerY = newY;
							moveCount++;
							playerPath[playerX][playerY] = '*'; // 标记走过的路径
						}
					}
				}
			}
		}
	}
}

// 生成迷宫
void generateMaze() {
	generateMazeSize();
	initializeMaze();

	// 使用DFS生成迷宫
	random_device rd;
	mt19937 gen(rd());
	int startDFSx = uniform_int_distribution<>(1, n - 2)(gen);
	int startDFSy = uniform_int_distribution<>(1, m - 2)(gen);
	generateMazeDFS(startDFSx, startDFSy);

	// 增加复杂度
	increaseComplexity();

	// 生成起点和终点
	generateStartEnd();
}

// 主函数
int main() {
	setNonBlockingMode();
	srand(time(0));

	while (true) {
		showMenu();
		char choice = getch();

		switch (choice) {
		case '1': // 开始游戏
			generateMaze();
			gameLoop();
			break;
		case '2': // 设置难度
			setDifficulty();
			break;
		case '3': // 游戏说明
			showInstructions();
			break;
		case '4': // 退出游戏
			clearScreen();
			cout << "谢谢游玩！再见！" << endl;
			restoreTerminal();
			return 0;
		default:
			cout << "\n无效选择，请重新输入！";
			sleep(1);
		}
	}

	restoreTerminal();
	return 0;
}
