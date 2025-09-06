#include <iostream>
#include <windows.h>
using namespace std;
int main () {
	SetConsoleOutputCP (CP_UTF8);
	SetConsoleCP (CP_UTF8);
	setlocale (LC_ALL, "en_US.UTF-8");
	while (1) {
		cout << "0.退出  1.加密  2.解密\n";
		int a;
		cin >> a;
		if (a == 0) {
			return 0;
		} else if (a == 1) {
			int result = system ("AES256sr.exe");
			if (result != 0) { cout << "AES256sr.exe执行失败!"; }
		} else {
			int result = system ("AES256sr-J.exe");
			if (result != 0) { cout << "AES256sr-J.exe执行失败!"; }
		}
		system("pause");
		system("cls");
	}
}