#include <bits/stdc++.h>
using namespace std;
int m, n;
vector<int> pa;
struct uu {
	int u, v, w;
	bool operator< (const uu &p) const {
		return w < p.w;
	}
};
int f (int x) {
	if (pa[x] != x) pa[x] = f (pa[x]);
	return pa[x];
}
bool ff (int x, int y) {
	x = f (x);
	y = f (y);
	if (x == y) return 0;
	pa[y] = x;
	return 1;
}
int o (int x, int y) {
	return (x - 1) * n + (y - 1);
}
int main () {
	cin >> m >> n;
	vector<uu> g;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (j < n) g.push_back ({o (i, j), o (i, j + 1), 2});
			if (i < m) g.push_back ({o (i, j), o (i + 1, j), 1});
		}
	}
	int x1, y1, x2, y2;
	while (cin >> x1 >> y1 >> x2 >> y2) {
		int u = o (x1, y1);
		int v = o (x2, y2);
		for (auto &e : g) {
			if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
				e.w = 0;
				break;
			}
		}
	}
	sort (g.begin (), g.end ());
	pa.resize (m * n);
	for (int i = 0; i < m * n; ++i) pa[i] = i;
	int ans = 0;
	for (auto e : g) {
		if (ff (e.u, e.v)) { ans += e.w; }
	}
	cout << ans;
	return 0;
}