#include <bits/stdc++.h>
using namespace std;
int dp[2017][2017], v[2017];
int main () {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) { cin >> v[i]; }
	for (int i = 1; i <= n; i++) { dp[i][i] = v[i] * n; }
	for (int i = 2; i <= n; i++) {
		for (int l = 1; l <= n; l++) {
			int r = l + i - 1;
			if (r > n) break;
			dp[l][r] = max (dp[l][r - 1] + v[r] * (n - i + 1), dp[l + 1][r] + v[l] * (n - i + 1));
		}
	}
	cout << dp[1][n];
	return 0;
}
