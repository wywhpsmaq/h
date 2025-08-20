#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int n, g[114][114], dp[114][114][1145];
int minn (int a, int b, int c, int d, int e) {
	return min (a, min (b, min (c, min (d, e))));
}
int ddpp (int x, int y, int s) {
	if (x < 0 || x >= n || y < 0 || y >= n) return inf;
	if (s < 0) return inf;
	if (x == n - 1 && y == n - 1) { return (s == 0) ? g[x][y] : inf; }
	if (s == 0) return inf;
	if (dp[x][y][s] != -1) return dp[x][y][s];
	int num = inf;
	num = minn (ddpp (x + 1, y, s - 1), ddpp (x, y + 1, s - 1), ddpp (x + 1, y + 1, s - 1), ddpp (x - 1, y, s - 1), ddpp (x, y - 1, s - 1));
	if (num == inf) {
		dp[x][y][s] = inf;
		return inf;
	}
	dp[x][y][s] = num + g[x][y];
	return dp[x][y][s];
}
int main () {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) { cin >> g[i][j]; }
	}
	memset (dp, -1, sizeof (dp));
	int ans = ddpp (0, 0, 2 * n - 2);
	cout << ans;
	return 0;
}