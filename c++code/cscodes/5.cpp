#include <bits/stdc++.h>
#include <windows.h> // 用于设置控制台编码
using namespace std;

int main () {
	freopen("1.txt","r",stdin);
	freopen("2.txt","w",stdout);
	// 设置控制台输入输出编码为UTF-8
	SetConsoleOutputCP (65001); // 输出编码
	SetConsoleCP (65001);		// 输入编码

	string chinese;
	cout << "请输入中文：";
	getline (cin, chinese);
	cout << "你输入的中文是：" << chinese << endl;

	return 0;
}