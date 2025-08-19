#include <bits/stdc++.h>
using namespace std;
long long dp[20005], a[110][110];
int main () {
	int s, n, m;
	cin >> s >> n >> m;
	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= n; j++) { cin >> a[j][i]; }
	}
	for (int i = 1; i <= n; i++) {
		sort (a[i] + 1, a[i] + s + 1);
		for (int j = m; j >= 0; j--) {
			for (int k = 1; k <= s; k++) {
				if (j <= a[i][k] * 2) continue;
				dp[j] = max (dp[j], dp[j - 2 * a[i][k] - 1] + i * k);
			}
		}
	}
	cout << dp[m];
	return 0;
}