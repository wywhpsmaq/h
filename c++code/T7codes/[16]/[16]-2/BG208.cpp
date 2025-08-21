#include <bits/stdc++.h>
using namespace std;
int f[1145][1145];
int main () {
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> f[i][i];
		ans = max (ans, f[i][i]);
	}
	for (int i = 2; i <= n; i++) {
		for (int l = 1; l + i - 1 <= n; l++) {
			int r = l + i - 1;
			for (int k = l; k < r; k++) {
				if (f[l][k] == f[k + 1][r] && f[l][k]) {
					f[l][r] = max (f[l][r], f[l][k] + 1);
					ans = max (ans, f[l][r]);
				}
			}
		}
	}
	cout << ans;
	return 0;
}
