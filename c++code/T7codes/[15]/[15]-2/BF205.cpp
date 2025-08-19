#include <bits/stdc++.h>
using namespace std;
int n, V, w[66], v[66], dp[66][115514];
vector<int> p[66];
void dfs (int x) {
	for (int i = w[x]; i <= V; i++) { dp[x][i] = v[x]; }
	for (int i = 0; i < p[x].size (); i++) {
		int y = p[x][i];
		dfs (y);
		for (int j = V; j >= w[x]; j--) {
			for (int k = 1; k <= j - w[x]; k++) { dp[x][j] = max (dp[x][j], dp[y][k] + dp[x][j - k]); }
		}
	}
}
int main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cin >> V >> n;
	V /= 10;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> w[i] >> v[i] >> x;
		w[i] /= 10;
		p[x].push_back (i);
		v[i] *= w[i];
	}
	dfs (0);
	cout << dp[0][V] * 10;
	return 0;
}