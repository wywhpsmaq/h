#include <bits/stdc++.h>
using namespace std;
int as, bs, cs, ds;
int dp[100][100][100][100];
int num[1145];
int main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) { cin >> num[i]; }
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		if (x == 1) as++;
		else if (x == 2) bs++;
		else if (x == 3) cs++;
		else ds++;
	}
	for (int a = 0; a <= as; a++) {
		for (int b = 0; b <= bs; b++) {
			for (int c = 0; c <= cs; c++) {
				for (int d = 0; d <= ds; d++) {
					int now = 1 + a + 2 * b + 3 * c + 4 * d;
					if (a != 0) dp[a][b][c][d] = max (dp[a][b][c][d], dp[a - 1][b][c][d] + num[now]);
					if (b != 0) dp[a][b][c][d] = max (dp[a][b][c][d], dp[a][b - 1][c][d] + num[now]);
					if (c != 0) dp[a][b][c][d] = max (dp[a][b][c][d], dp[a][b][c - 1][d] + num[now]);
					if (d != 0) dp[a][b][c][d] = max (dp[a][b][c][d], dp[a][b][c][d - 1] + num[now]);
				}
			}
		}
	}
	cout << dp[as][bs][cs][ds] + num[1];
	return 0;
}