#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
void js (int num) {
	for (int i = num; i >= 0; i--) {
		std::this_thread::sleep_for (std::chrono::milliseconds (1000));
		std::cout << "\b" << i;
	}
}
bool ping () {
	string ccs = "ping -n 1 -w 1000 8.8.8.8 > nul";
	const int jg = system (ccs.c_str ());
	return !jg;
}
vector<int> sr () {
	vector<int> p;
	freopen ("cs\\cs.txt", "r", stdin);
	for (int i = 0; i < 4; i++) {
		int a;
		cin >> a;
		p.push_back (a);
	}
	return p;
}
void sc (vector<int> p) {
	freopen ("114514.txt", "r", stdin);
	freopen ("cs\\cs.txt", "w", stdout);
	for (int i : p) { cout << i << '\n'; }
}
int main () {
		SetConsoleOutputCP (CP_UTF8);
		SetConsoleCP (CP_UTF8);
		setlocale (LC_ALL, "en_US.UTF-8");
	random_device rd;
	mt19937 gen (rd ());
	uniform_int_distribution<> f (1, 10);
	if (!ping ()) {
		cout << "你的网络有问题，无法追踪定向服务器！！！\n";
		system ("pause");
		return 0;
	}
	cout << "如果你要玩PCL2请输入0并按Enter\n如果你要玩PCL2社区版请输入1并按Enter\n如果你要玩zj-1创请输入2并按Enter\n如果你要玩ZJ-2创请输入3并按Enter\n";
	int a;
	cin >> a;
	if (a == 0) {
		vector<int> num = sr ();
		if (num[a] == 0) {
			cout << "您的次数已经用完，无法启动！！！";
			return 0;
		}
		cout << "你只剩" << num[a] << "次，你确定要启动吗？如果是请等待环境检测结束，否则请关闭窗口。环境检测结束剩余：";
		js (f (gen));
		cout << '\n';
		num[a]--;
		sc (num);
		system ("start yx-2\\PCL2\\PCL2.exe");
	} else if (a == 1) {
		vector<int> num = sr ();
		if (num[a] == 0) {
			cout << "您的次数已经用完，无法启动！！！\n";
			return 0;
		}
		cout << "你只剩" << num[a] << "次，你确定要启动吗？如果是请等待环境检测结束，否则请关闭窗口。环境检测结束剩余：";
		js (f (gen));
		cout << '\n';
		num[a]--;
		sc (num);
		system ("start yx-2\\PCL2_CE\\PCL2_CE.exe");
	} else if (a == 2) {
		vector<int> num = sr ();
		if (num[a] == 0) {
			cout << "您的次数已经用完，无法启动！！！\n";
			return 0;
		}
		cout << "你只剩" << num[a] << "次，你确定要启动吗？如果是请等待环境检测结束，否则请关闭窗口。环境检测结束剩余：";
		js (f (gen));
		cout << '\n';
		num[a]--;
		sc (num);
		system ("start yx-2\\ZJ-1\\PlantsVsZombiesRH.exe");
	} else if (a == 3) {
		vector<int> num = sr ();
		if (num[a] == 0) {
			cout << "您的次数已经用完，无法启动！！！\n";
			return 0;
		}
		cout << "你只剩" << num[a] << "次，你确定要启动吗？如果是请等待环境检测结束，否则请关闭窗口。环境检测结束剩余：";
		js (f (gen));
		cout << '\n';
		num[a]--;
		sc (num);
		system ("start yx-2\\ZJ-2\\PlantsVsZombiesRH.exe");
	} else {
		cout << "cnm,没有这个选项";
	}
}