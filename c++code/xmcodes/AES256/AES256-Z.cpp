#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
void js () {
	int a = time (0);
	while (a + 2 != time (0)) {}
	return;
}
int main () {
	SetConsoleOutputCP (CP_UTF8);
	SetConsoleCP (CP_UTF8);
	setlocale (LC_ALL, "en_US.UTF-8");
	freopen ("yyz.txt", "r", stdin);
	freopen ("yz.txt", "w", stdout);
	int a;
	string s = "", s1 = "";
	cin >> a >> s >> s1;
	if (a == 0) {
		freopen ("AES256-q.txt", "w", stdout);
		cout << s1 << '\n' << s << '\n';
		freopen ("yz.txt", "w", stdout);
		cout << 1 << '\n';
		system ("AES256sr.exe");
		js ();
		freopen ("AES256-q1.txt", "r", stdin);
		string ss = "";
		getline (cin, ss);
		vector<pair<string, string>> v;
		freopen ("gg.txt", "r", stdin);
		string ss1, ss2;
		while (cin >> ss1 >> ss2) { v.push_back (make_pair (ss1, ss2)); }
		v.push_back (make_pair (s, ss));
		freopen ("yyz.txt", "r", stdin);
		freopen ("gg.txt", "w", stdout);
		for (auto i : v) { cout << i.first << '\n' << i.second << '\n'; }
		return 0;
	} else if (a == 1) {
		string ss;
		freopen ("gg.txt", "r", stdin);
		while (cin >> ss && ss != s) {}
		cin >> ss;
		freopen ("AES256-p.txt", "w", stdout);
		cout << s1 << '\n' << ss;
		freopen ("yz.txt", "w", stdout);
		freopen ("AES256-p1.txt", "r", stdin);
		system ("AES256sr-J.exe");
		js ();
		ss = "";
		getline (cin, ss);
		cout << ((ss == s) ? 1 : 0);
		return 0;
	} else {
		freopen ("yz.txt", "w", stdout);
		return 1;
	}
}