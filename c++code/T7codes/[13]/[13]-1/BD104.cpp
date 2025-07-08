#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g;
vector<bool> vis;
vector<int> p;
int n;
int dfs (int u, int num) {
	if (num == n) {
		if (g[u][p[0]]) {
			p.push_back (p[0]);
			return 1;
		}
		return 0;
	}
	for (int v = 0; v < n; ++v) {
		if (!vis[v] && g[u][v]) {
			vis[v] = 1;
			p.push_back (v);
			if (dfs (v, num + 1)) return 1;
			p.pop_back ();
			vis[v] = 0;
		}
	}
	return 0;
}
int main () {
	while (cin >> n && n) {
		g.assign (n, vector<int> (n));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) { cin >> g[i][j]; }
		}
		bool f = 0;
		for (int i = 0; i < n; ++i) {
			p.clear ();
			vis.assign (n, 0);
			p.push_back (i);
			vis[i] = 1;
			if (dfs (i, 1)) {
				for (int i = 0; i < p.size (); ++i) { cout << p[i] + 1 << " "; }
				cout << '\n';
				f = 1;
				break;
			}
		}
		if (!f) cout << "-1" << '\n';
	}
	return 0;
}