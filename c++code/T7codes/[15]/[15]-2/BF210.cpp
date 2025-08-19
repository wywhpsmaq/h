#include <bits/stdc++.h>
using namespace std;
int ans[1100][1100];
int a, b, c;
int main () {
	int n, t, m;
	cin >> t >> m >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		for (int j = t; j >= a; j--) {
			for (int k = m; k >= b; k--) { ans[j][k] = max (ans[j][k], ans[j - a][k - b] + c); }
		}
	}
	cout << ans[t][m];
}