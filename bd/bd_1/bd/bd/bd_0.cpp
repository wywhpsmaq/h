#include <bits/stdc++.h>
using namespace std;
int main () {
	freopen ("v.vbs", "w", stdout);
	string s = " msgbox\"hahaha\" ";
	for (int i = 1; i <= 100; i++) cout << s << endl;
	freopen ("v2.vbs", "w", stdout);
	cout << "dim k" << endl << "k=1" << endl << "while k<101" << endl << "k=k+1" << endl << "msgbox k" << endl << "Wend";
	freopen ("v3.bat", "w", stdout);
	cout << "cmd";
	int n;
	n = 999;
	freopen ("v4.bat", "w", stdout);
	for (int i = 1; i <= n; i++) system ("start v3.bat");
	system ("start v2.vbs");
	system ("start v.vbs");
	return 0;
}