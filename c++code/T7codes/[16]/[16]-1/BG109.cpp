#include <bits/stdc++.h>
using namespace std;
int n, g[11][11], dp[11][11][11][11];
bool vis[11][11];
int dfs (int x1, int y1, int x2, int y2) {
	if (!((x1 >= 1) && (x1 <= n) && (y1 >= 1) && (y1 <= n)) || !((x2 >= 1) && (x2 <= n) && (y2 >= 1) && (y2 <= n))) return -1;
	if (x1 == n && y1 == n && x2 == n && y2 == n) return 0;
	if (dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
	int res = -1;
	for (int d1 = 0; d1 <= 1; d1++) {
		for (int d2 = 0; d2 <= 1; d2++) {
			int dx = x1 + d1, dy = y1 + (1 - d1);
			int dx1 = x2 + d2, dy1 = y2 + (1 - d2);
			int sum = dfs (dx, dy, dx1, dy1), num;
			if (sum == -1) continue;
			if (x1 == x2 && y1 == y2) {
				num = g[x1][y1];
			} else {
				num = g[x1][y1] + g[x2][y2];
			}
			res = max (res, sum + num);
		}
	}
	return dp[x1][y1][x2][y2] = res;
}
int main () {
	cin >> n;
	memset (g, 0, sizeof (g));
	memset (dp, -1, sizeof (dp));
	int x, y, v;
	while (cin >> x >> y >> v && x != 0) { g[x][y] = v; }
	int ans = dfs (1, 1, 1, 1) + g[1][1];
	cout << ans;
	return 0;
}