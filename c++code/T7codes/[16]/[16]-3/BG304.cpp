#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> v;
int n, m, dp[310][310], s[310];
void dfs (int x) {
	for (int i : v[x]) {
		dfs (i);
		for (int j = m; j >= 1; j--) {
			for (int k = 0; k <= j - 1; k++) { dp[x][j] = max (dp[x][j], dp[i][k] + dp[x][j - k - 1] + s[i]); }
		}
	}
}
int main () {
	cin >> n >> m;
	v.resize (n + 10);
	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k >> s[i];
		v[k].push_back (i);
	}
	dfs (0);
	cout << dp[0][m];
	return 0;
}