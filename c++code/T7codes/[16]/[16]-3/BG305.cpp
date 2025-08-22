#include <bits/stdc++.h>
using namespace std;
vector<int> e[1145144];
int f[1145144], ans;
void dfs (int u, int fa) {
	int max1 = 0, max2 = 0;
	for (int i = 0, v; i < e[u].size (); i++)
		if ((v = e[u][i]) != fa) {
			dfs (v, u);
			f[u] = max (f[u], f[v]);
			if (f[v] > max1) max2 = max1, max1 = f[v];
			else if (f[v] > max2) max2 = f[v];
		}
	int num = e[u].size () - (fa != -1);
	f[u] += (1 + max (0, num - 1));
	ans = max (ans, max1 + max2 + 1 + max (0, num - 1 - (fa == -1)));
}
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		e[u].push_back (v);
		e[v].push_back (u);
	}
	dfs (1, -1);
	cout << ans;
	return 0;
}
