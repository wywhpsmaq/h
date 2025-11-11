/*
0.注册：从yyz.txt中读入“0\n用户名\n密码”，由本程序进行操作
1.登录：从yyz.txt中读入“1\n0或1(普通用户/管理员)(如果是管理员则添加"\n管理员密码")\n用户名\n密码”，由本程序验证
2.添加：从yyz.txt中读入“2\n添加的数据”，由本程序添加到public//sj.txt中
3.删除：从yyz.txt中读入”3\n需要删除的数据个数 需要删除的编号(用空格隔开)“，由本程序从public//sj.txt中删除
4.导入：目前由server.js直接替换public//sj.txt中的内容
5.导出：目前由server.js直接从public//sj.txt中打包成.csv文件
6.密码修改：从yyz.txt中读入“6\n用户名\n新密码”，由本程序修改gg.txt中的对应信息
100.加载：从yyz中读入“100\n123465”，由本程序从data//sf.txt文件中解密并替换public//sj.txt中的内容
101.保存：从yyz中读入“101\n123456”，由本程序从public//sj.txt读取数据并使用加密后的内容替换data//sf.txt中的内容


==========================未完成===========================


7.验证权限信息：从yyz.txt中读入“7\n用户名\n需要验证的权限信息个数 需要验证是否拥有的权限信息(用空格隔开)”，由本程序验证qx.txt中的对应信息
8.修改权限信息：从yyz.txt中读入“8\n用户名\n新的权限信息序列”，由本程序修改qx.txt中的对应信息
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
void js () {
	int a = time (nullptr);
	while (a + 2 != time (nullptr)) {}
}
void sx () {
	fflush (stdin);
	fflush (stdout);
}
int main () {
	SetConsoleOutputCP (CP_UTF8);
	SetConsoleCP (CP_UTF8);
	setlocale (LC_ALL, "en_US.UTF-8");
	freopen ("yyz.txt", "r", stdin);
	//	freopen ("yz.txt", "w", stdout);
	int a;
	cin >> a;
	if (a == 0) { // 注册
		string s, s1;
		cin >> s >> s1;
		freopen ("AES256-q.txt", "w", stdout);
		cout << s1 << '\n' << s << '\n';
		freopen ("yz.txt", "w", stdout);
		cout << 1 << '\n';
		system ("1-AES256.exe");
		js ();
		freopen ("AES256-q1.txt", "r", stdin);
		string ss;
		getline (cin, ss);
		vector<pair<string, string>> v;
		freopen ("gg.txt", "r", stdin);
		string ss1, ss2;
		while (cin >> ss1 >> ss2) {
			v.push_back (make_pair (ss1, ss2));
		}
		v.push_back (make_pair (s, ss));
		freopen ("yyz.txt", "r", stdin);
		freopen ("gg.txt", "w", stdout);
		for (auto i : v) {
			cout << i.first << '\n' << i.second << '\n';
		}
		return 0;
	} else if (a == 1) { // 登录
		int g;
		cin >> g;
		if (g == 0) { // 普通用户登录
			string s, s1;
			cin >> s >> s1;
			string ss;
			freopen ("gg.txt", "r", stdin);
			while (cin >> ss && ss != s) {}
			cin >> ss;
			freopen ("AES256-p.txt", "w", stdout);
			cout << s1 << '\n' << ss;
			freopen ("yz.txt", "w", stdout);
			freopen ("AES256-p1.txt", "r", stdin);
			system ("1-AES256-J.exe");
			js ();
			ss = "";
			getline (cin, ss);
			cout << ((ss == s) ? 1 : 0);
			return 0;
		} else if (g == 1) { // 管理员登录
			string s, s1, s2;
			cin >> s >> s1 >> s2;
			if (s2 != "wyw-admin.2025") { // 暂时写死管理员密码
				freopen ("yz.txt", "w", stdout);
				cout << 0 << '\n';
				return 0;
			}
			string ss;
			freopen ("gg.txt", "r", stdin);
			while (cin >> ss && ss != s) {}
			cin >> ss;
			freopen ("AES256-p.txt", "w", stdout);
			cout << s1 << '\n' << ss;
			freopen ("yz.txt", "w", stdout);
			freopen ("AES256-p1.txt", "r", stdin);
			system ("1-AES256-J.exe");
			js ();
			ss = "";
			getline (cin, ss);
			cout << ((ss == s) ? 1 : 0);
			return 0;
		}
	} else if (a == 2) { // 添加
		string s, s1;
		while (cin >> s1) {
			s += s1 + " ";
		}
		std::ofstream outFile ("public\\sj.txt", std::ios::app);
		fflush (stdout);
		// freopen ("public\\sj.txt", "w", stdout);
		outFile << s << '\n';

		// string s, s1;
		// // 从文件中读取数据
		// getline (cin, s);
		// getline (cin, s1);
		// // 写入并调用加密
		// freopen ("AES256-q.txt", "w", stdout);
		// cout << s << '\n' << s1 << '\n';
		// fflush (stdout);
		// system ("1-AES256.exe");
		// // 读取数据并添加到文件末尾
		// freopen ("AES256-q1.txt", "r", stdin);
		// string ss;
		// getline (cin, ss);
		// std::ofstream file ("data//sf.txt", std::ios::app);
		// file << ss;
	} else if (a == 3) { // 删除
		int n;
		string s;
		vector<int> v;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			v.push_back (x);
		}
		freopen ("public\\sj.txt", "r", stdin);
		fflush (stdin);
		int l = 0;
		vector<string> p;
		while (cin >> s) {
			int x = 0, i = 0;
			while ('0' <= s[i] && s[i] <= '9') {
				x *= 10, x += s[i] - '0', i++;
			}
			if (l < n && x == v[l]) {
				l++;
			} else p.push_back (s);
		}
		freopen ("public\\sj.txt", "w", stdout);
		fflush (stdout);
		for (auto i : p) {
			cout << i << '\n';
		}
	} else if (a == 4) { // 导入
		// 目前由后端直接替换
		/*
		// 读取文件并加密
		// 将加密后的数据添加到文件末尾
		*/
	} else if (a == 5) { // 导出
		// 目前由后端直接导出
		/*
		// 解密文件
		// 把解密后文数据输出到文件中
		*/
	} else if (a == 6) { // 密码修改
		string s, s1;
		cin >> s >> s1;
		string ss, ss1;
		vector<string> p;
		freopen("gg.txt", "r", stdin);
		while (cin >> ss >> ss1) {
			if (ss != s) p.push_back (ss + "\n" + ss1);
		}
		// 写入并调用加密
		freopen ("AES256-q.txt", "w", stdout);
		cout << s1 << '\n' << s << '\n';
		fflush (stdout);
		system ("1-AES256.exe");
		js ();
		freopen ("gg.txt", "w", stdout);
		fflush (stdout);
		ifstream fin ("AES256-q1.txt");
		fflush(stdin);
		for (auto i : p) {
			cout << i << '\n';
		}
		string s2;
		fin >> s2;
		cout << s << "\n" << s2 << "\n";
	} else if (a == 7) {   // 验证权限信息
	} else if (a == 8) {   // 修改权限信息
	} else if (a == 100) { // 加载
		string s, s1;
		cin >> s1;
		// 解密数据
		freopen ("data\\sf.txt", "r", stdin);
		getline (cin, s);
		freopen ("AES256-p.txt", "w", stdout);
		cout << s1 << '\n' << s << '\n';
		fflush (stdout);
		system ("1-AES256-J.exe");
		js ();
		// 解析并输出到动态文件中
		freopen ("AES256-p1.txt", "r", stdin);
		fflush (stdin);
		freopen ("public\\sj.txt", "w", stdout);
		ifstream fin ("AES256-p1.txt");
		char c;
		while (fin >> c) {
			if (c == '\\') {
				fin >> c;
				cout << '\n';
			} else cout << c;
		}
	} else if (a == 101) { // 保存
		// 输入动态文件中的内容
		string s, s1, s2;
		string ss;
		cin >> s2;
		ifstream fin ("public\\sj.txt");
		// freopen ("public\\sj.txt", "r", stdin);
		fflush (stdin);
		while (fin >> s1) {
			s += s1;
			s += "\\n";
		}
		// 加密并替换文件内容
		freopen ("AES256-q.txt", "w", stdout);
		fflush (stdout);
		cout << s2 << '\n' << s << '\n';
		fflush (stdout);
		system ("1-AES256.exe");
		js ();
		fflush (stdin);
		freopen ("AES256-q1.txt", "r", stdin);
		fflush (stdin);
		getline (cin, ss);
		fflush (stdout);
		freopen ("data\\sf.txt", "w", stdout);
		fflush (stdout);
		cout << ss;
	} else {
		freopen ("yz.txt", "w", stdout);
		return 1;
	}
	freopen ("yz.txt", "w", stdout);
	cout << "1\n";
	return 0;
}
/*
 文件：
 1.yyz.txt：后端输入文件
 2.yz.txt：后端结果文件
 3.yzz.txt：暂无作用
 4.AES256-p.txt：解密输入
 5.AES256-p1.txt：解密输出
 6.AES256-q.txt：加密输入
 7.AES256-q1.txt：加密输出
 8.gg.txt：用户登录信息储存
 9.data\\sf.txt：加密后的信息储存
 10.public\\sj.txt：信息解密结果临时储存
 11.qx.txt：用户权限信息储存(目前不加密)
 */
