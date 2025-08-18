#include <bits/stdc++.h>
using namespace std;
int dp[114514], p[110][110];
int main () {
	int t, n, m, ans;
	cin >> t >> n >> m;
	for (int i = 1; i <= t; ++i) {
		for (int j = 1; j <= n; ++j) {
            cin >> p[i][j];
        }
	}
	ans = m;
	for (int i = 1; i < t; ++i) {
		memset (dp, -0x3f, sizeof (dp));
		dp[ans] = ans;
		for (int j = 1; j <= n; ++j) {
			for (int k = ans; k >= p[i][j]; --k) {
                dp[k - p[i][j]] = max (dp[k - p[i][j]], dp[k] + p[i + 1][j] - p[i][j]);
            }
		}
		int ma = 0;
		for (int j = 0; j <= ans; ++j) {
            ma = max (ma, dp[j]);
        }
		ans = ma;
	}
	cout << ans;
	return 0;
}
