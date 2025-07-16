#include <bits/stdc++.h>
using namespace std;
int a[1145], b[1145], f[1145][1145];
int main () {
	int n, x, y, z;
	cin >> n >> x >> y >> z;
	int l, r;
	l = r = 1;
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		for (int j = 1; j <= x; j++) a[l++] = i;
		for (int l = 1; l <= y; l++) b[r++] = i;
	}
	for (int i = 1; i <= l; i++) f[i][0] = i * y;
	for (int i = 1; i <= r; i++) f[0][i] = i * x;
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= r; j++) { f[i][j] = min (f[i - 1][j] + y, min (f[i][j - 1] + x, f[i - 1][j - 1] + z * abs (a[i] - b[j]))); }
	}
	cout << f[l][r];
	return 0;
}