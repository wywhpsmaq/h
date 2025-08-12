#include <bits/stdc++.h>
using namespace std;
int p[1145][1145];
int main () {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		p[x + 2][y + 2] = 1;
	}
	int ans = 0;
	for (int i = 3; i <= n + 2; i++) {
		for (int j = 3; j <= m + 2; j++) {
			if (p[i][j]) continue;
			int nn = 0;
			if (p[i - 1][j - 1]) nn++;
			if (p[i - 1][j]) nn++;
			if (p[i - 1][j + 1]) nn++;
			if (p[i][j - 1]) nn++;
			if (p[i][j + 1]) nn++;
			if (p[i + 1][j - 1]) nn++;
			if (p[i + 1][j]) nn++;
			if (p[i + 1][j + 1]) nn++;
			if (p[i + 2][j]) nn++;
			if (p[i][j + 2]) nn++;
			if (p[i - 2][j]) nn++;
			if (p[i][j - 2]) nn++;
			ans = max (ans, nn);
		}
	}
	cout << ans;
}