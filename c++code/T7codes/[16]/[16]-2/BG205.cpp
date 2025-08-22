#include <bits/stdc++.h>
using namespace std;
int dp[114][114];
int main () {
	string s;
	cin >> s;
	int n = s.size ();
	for (int i = 0; i < n; ++i) {
		dp[i][i] = 1;
	}
	for (int l = 1; l < n; ++l) {
		for (int i = 0; i + l < n; ++i) {
			if (s[i] == s[i + l]) {
				dp[i][i + l] = dp[i][i + l - 1];
			} else {
				dp[i][i + l] = dp[i][i] + dp[i + 1][i + l];
				for (int k = i + 1; k < i + l; ++k) { dp[i][i + l] = min (dp[i][i + l], dp[i][k] + dp[k + 1][i + l]); }
			}
		}
	}
	cout << dp[0][n - 1];
	return 0;
}
