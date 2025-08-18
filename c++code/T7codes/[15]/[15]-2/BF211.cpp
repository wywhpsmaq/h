#include <bits/stdc++.h>
using namespace std;
int v, n, t, x;
int w[10001], z[10001], b[10001];
int g[205][205];
int dp[10001];
int main () {
	cin >> v >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> z[i] >> x;
		t = max (t, x);
		b[x]++;
		g[x][b[x]] = i;
	}
	for (int i = 1; i <= t; i++) {
		for (int j = v; j >= 0; j--) {
			for (int k = 1; k <= b[i]; k++) {
				if (j >= w[g[i][k]]) { dp[j] = max (dp[j], dp[j - w[g[i][k]]] + z[g[i][k]]); }
			}
		}
	}
	cout << dp[v];
	return 0;
}
