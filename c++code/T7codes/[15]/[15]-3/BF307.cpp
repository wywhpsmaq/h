#include <bits/stdc++.h>
using namespace std;
#define ing long long
int dp[1145144], g[1145144];
signed main () {
	int n, v, p, a, b, c;
	cin >> n >> v;
	for (int i = 1; i <= n; i++) {
		cin >> p >> a;
		for (int j = p; j <= v; j++) g[j] = dp[j - p];
		for (int j = 1; j <= a; j++) {
			cin >> b >> c;
			for (int k = v - b; k >= p; k--) g[k + b] = max (g[k + b], g[k] + c);
		}
		for (int j = p; j <= v; j++) dp[j] = max (g[j], dp[j]);
	}
	cout << dp[v];
	return 0;
}