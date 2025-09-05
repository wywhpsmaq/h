#include <bits/stdc++.h>
#include <windows.h> // 用于设置控制台编码
using namespace std;

int main () {
	// freopen ("1.txt", "r", stdin);
	// freopen ("2.txt", "w", stdout);
	SetConsoleOutputCP (65001);
	SetConsoleCP (65001);

	// int a[114] = {};
	// for (int i = 0; i < 4; i++) {
	// 	random_device rd;
	// 	mt19937 gen (rd ());
	// 	uniform_int_distribution<> f (10, 15);
	// 	a[i] = f (gen);
	// }
	// string ch[114];
	// cout << "请输入中文：";
	// for (int i = 0; i < 4; i++) {
	// 	getline (cin, ch[i]);
	// 	ch[i] ^= a[i];
	// }

	string c;
    //cin>>c;
    c.resize(3);
    c[0]=-26,c[1]=-99,c[2]=-114;
	cout << c[0] << c[1] << c[2] << '\n';
	return 0;
}