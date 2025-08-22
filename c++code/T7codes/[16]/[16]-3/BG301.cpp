#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> p[114514];
int zj = 0, fa = 1;
void dfs (int x, int v, int z) {
	if (z > zj) {
		zj = z;
		fa = x;
	}
	for (auto i : p[x]) {
		auto [d, da] = i;
		if (d != v) { dfs (d, x, z + da); }
	}
}
int main () {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		p[u].push_back ({v, w});
		p[v].push_back ({u, w});
	}
	zj = 0;
	dfs (1, 0, 0);
	int s = fa;
	zj = 0;
	dfs (s, 0, 0);
	cout << zj;
	return 0;
}