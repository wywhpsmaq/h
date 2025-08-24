#include <bits/stdc++.h>
using namespace std;
int n, m;
struct uu {
	int d, v;
};
vector<vector<uu>> g;
int dp[114][114];
int vis[114];
int dfs (int e, int fa) {
	int ans = 0;
	for (int i = 0; i < g[e].size (); i++) {
		int ds = g[e][i].d;
		if (ds == fa) continue;
		ans += dfs (ds, e) + 1;
		for (int j = min (m, ans); j >= 0; --j) {
			for (int k = j; k > 0; --k) { dp[e][j] = max (dp[e][j], dp[e][j - k] + dp[ds][k - 1] + g[e][i].v); }
		}
	}
	return ans;
}
int main () {
	cin >> n >> m;
	g.clear ();
	g.resize (n + 10);
	for (int i = 1; i < n; ++i) {
		int s, d, v;
		cin >> s >> d >> v;
		g[s].push_back ({d, v});
		g[d].push_back ({s, v});
	}
	dfs (1, -1);
	cout << dp[1][m];
	return 0;
}
