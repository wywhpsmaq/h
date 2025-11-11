#include <bits/stdc++.h>
int N, K, V, dp[5145][5145];
using namespace std;
int main () {
	cin >> K >> V >> N;
	memset (dp, -0x3f, sizeof dp);
	dp[0][1] = 0;
	for (int i = 0; i < N; i++) {
		int w, v;
		cin >> w >> v;
		for (int j = V; j >= w; j--) {
			int p1 = 1, p2 = 1, t[114];
			for (int k = 1; k <= K; k++) {
				if (dp[j][p1] > dp[j - w][p2] + v) {
					t[k] = dp[j][p1];
					p1++;
				} else {
					t[k] = dp[j - w][p2] + v;
					p2++;
				}
			}
			for (int k = 1; k <= K; k++) { dp[j][k] = t[k]; }
		}
	}
	int ans = 0;
	for (int i = 1; i <= K; i++) ans += dp[V][i];
	cout << ans;
}
