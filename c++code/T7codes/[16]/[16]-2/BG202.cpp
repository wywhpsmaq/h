#include <bits/stdc++.h>
using namespace std;
int dp[1145][1145], dpp[1145][1145];
int sum[1145];
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	int n, x[114514];
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		sum[i] = sum[i - 1] + x[i];
		dp[i][i] = dp[i + n][i + n] = 0;
	}
	for (int i = 1; i <= n; i++) { sum[n + i] = sum[n + i - 1] + x[i]; }
	memset (dp, 0, sizeof (dp));
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i + l - 1 <= 2 * n; i++) {
			int j = i + l - 1;
			dp[i][j] = INT_MAX;
			dpp[i][j] = INT_MIN;
			for (int k = i; k < j; k++) {
				dp[i][j] = min (dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]),
				dpp[i][j] = max (dpp[i][j], dpp[i][k] + dpp[k + 1][j] + sum[j] - sum[i - 1]);
			}
		}
	}
	int ans = INT_MAX, anss = INT_MIN;
	for (int i = 1; i <= n; i++) {
		ans = min (ans, dp[i][i + n - 1]);
		anss = max (anss, dpp[i][i + n - 1]);
	}
	cout << ans << '\n' << anss;
}