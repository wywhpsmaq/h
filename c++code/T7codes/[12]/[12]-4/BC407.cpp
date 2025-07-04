#include <bits/stdc++.h>
using namespace std;
int n, m, p, x, y;
int fa[114514], e[114514];
int f (int x) {
	if (fa[x] != x) fa[x] = f (fa[x]);
	return fa[x];
}
void ff (int x, int y) {
	x = f (x), y = f (y);
	if (x != y) fa[x] = y;
}
int main () {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i, e[i] = 0;
	for (int i = 1; i <= m; i++) {
		cin >> p >> x >> y;
		if (p == 0) {
			int fx = f (x), fy = f (y);
			ff (fx, fy);
			int ex = e[fx], ey = e[fy];
			if (ex && ey) ff (ex, ey);
			if (ex) e[f (fx)] = ex;
			if (ey) e[f (fy)] = ey;
		} else {
			int fx = f (x), fy = f (y);
			if (fx == fy) continue;
			if (!e[fx]) e[fx] = fy;
			else ff (e[fx], fy);
			if (!e[fy]) e[fy] = fx;
			else ff (e[fy], fx);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (fa[i] == i) ans++;
	}
	cout << ans;
	return 0;
}