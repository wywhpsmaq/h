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
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		ff (x, y);
	}
	cin >> p;
	for (int i = 1; i <= p; i++) {
		cin >> x >> y;
		if (f (x) == f (y)) cout << "Yes\n";
		else cout << "No\n";
	}
}