#include <bits/stdc++.h>
using namespace std;
int dp[1145][1145];
int sum[1145];
int main () {
	ios::sync_with_stdio(false);
    cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		sum[i] = sum[i - 1] + x;
	}
	memset (dp, 0, sizeof (dp));
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i + l - 1 <= n; i++) {
			int j = i + l - 1;
			dp[i][j] = INT_MAX;
			for (int k = i; k < j; k++) { dp[i][j] = min (dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1]); }
		}
	}
	cout << dp[1][n];
}