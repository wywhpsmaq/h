#include <bits/stdc++.h>
using namespace std;
int n, m, p, x, y;
int fa[114514], e[114514];
int f(int x) {
	if (fa[x] != x) fa[x] = f(fa[x]);
	return fa[x];
}
void ff(int x, int y) {
	x = f(x), y = f(y);
	if (x != y) fa[x] = y;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i, e[i] = 0;
	for (int i = 1; i <= m; i++) {
		cin >> p >> x >> y;
		if (p == 0) {
			ff(x, y);
		} else {
			if (e[y]) ff(e[y], x);
			else e[y] = x;
			if (e[x]) ff(e[x], y);
			else e[x] = y;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (fa[i] == i) ans++;//=if (f(i) == i) ans++;
	}
	cout << ans;
	return 0;
}