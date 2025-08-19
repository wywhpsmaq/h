#include <bits/stdc++.h>
using namespace std;
int fa[114514], sum[114514], v[114514], snm;
bool f[114514];
inline int ff (int x) {
	if (fa[x] == x) return x;
	return fa[x] = ff (fa[x]);
}
int main () {
	int n, m, num;
	cin >> n >> num >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		int fx = ff (x), fy = ff (y);
		if (fx == fy) continue;
		fa[fy] = fx;
	}
	for (int i = 1; i <= n; i++) {
		if (!sum[ff (i)]) sum[fa[i]] = ++snm;
		v[sum[fa[i]]]++;
	}
	f[0] = 1;
	for (int i = 1; i <= snm; i++) {
		for (int j = num << 1; j >= v[i]; j--) { f[j] |= f[j - v[i]]; }
	}
	for (int i = 0; i <= num; i++) {
		if (f[num - i]) {
			cout << num - i;
			return 0;
		}
		if (f[num + i]) {
			cout << num + i;
			return 0;
		}
	}
}