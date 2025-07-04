#include <bits/stdc++.h>
using namespace std;
int n, m, p, x, y;
int fa[1000000];
int f (int x) {
	if (x == fa[x]) return x;
	return fa[x] = f (fa[x]);
}
void ff (int x, int y) {
	int f1 = f (x), f2 = f (y);
	if (f1 != f2) fa[f1] = f2;
}
int main () {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		ff (x, y);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i == fa[i]) ans++;
	}
	cout << ans;
}