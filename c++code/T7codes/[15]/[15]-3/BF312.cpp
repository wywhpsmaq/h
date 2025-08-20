#include <bits/stdc++.h>
using namespace std;
int fa[10001];
int xz (int x) {
	if (fa[x] == x) { return x; }
	return fa[x] = xz (fa[x]);
}
int c[10001], d[10001], f[10001];
int main () {
	int n, m, w;
	cin >> n >> m >> w;
	for (int i = 1; i <= n; i++) { fa[i] = i; }
	for (int i = 1; i <= n; i++) { cin >> c[i] >> d[i]; }
	int x, y;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		fa[xz (x)] = xz (y);
	}
	for (int i = 1; i <= n; i++) {
		if (fa[i] != i) {
			d[xz (i)] += d[i];
			d[i] = 0;
			c[xz (i)] += c[i];
			c[i] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int v = w; v >= c[i]; v--) { f[v] = max (f[v], f[v - c[i]] + d[i]); }
	}
	cout << f[w];
	return 0;
}