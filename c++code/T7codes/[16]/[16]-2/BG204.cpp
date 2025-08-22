#include <bits/stdc++.h>
using namespace std;
int dp[1145][1145][2], p[114514], s[114514], sum[114514];
int main () {
	int n, e;
	cin >> n >> e;
	for (int i = 1; i <= n; i++) {
		cin >> s[i] >> p[i];
		sum[i] = sum[i - 1] + p[i];
	}
	memset (dp, 0x3f, sizeof dp);
	dp[e][e][0] = dp[e][e][1] = 0;
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			dp[i][j][0] = min (dp[i + 1][j][0] + ((sum[i] + sum[n] - sum[j]) * (s[i + 1] - s[i])),
							   dp[i + 1][j][1] + ((sum[i] + sum[n] - sum[j]) * (s[j] - s[i])));
			dp[i][j][1] = min (dp[i][j - 1][0] + ((sum[i - 1] + sum[n] - sum[j - 1]) * (s[j] - s[i])),
							   dp[i][j - 1][1] + ((sum[i - 1] + sum[n] - sum[j - 1]) * (s[j] - s[j - 1])));
		}
	}
	cout << min (dp[1][n][0], dp[1][n][1]);
}