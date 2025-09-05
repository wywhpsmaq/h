#include <bits/stdc++.h>
#include <windows.h> // 用于设置控制台编码
using namespace std;

int main () {
	freopen ("1.txt", "r", stdin);
	freopen ("2.txt", "w", stdout);
	SetConsoleOutputCP (65001);
	SetConsoleCP (65001);
	int a[114]={};
	for(int i=0;i<4;i++)
	{
		random_device rd;
		mt19937 gen (rd());
		uniform_int_distribution<> f(10,15);
		a[i] = f(gen);
	}
	string ch[114];
	cout << "请输入中文：";
	for (int i = 0; i < 4; i++) { 
		getline (cin, ch[i]);
		ch[i]^=a[i];
	}
	cout << "你输入的中文是：" << ch[0] << endl;
	return 0;
}