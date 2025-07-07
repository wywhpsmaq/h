#include<bits/stdc++.h>
using namespace std;
int f[1145144], s[1145144], d[1145144];
int ff(int o) {
	if (f[o] == o) return o;
	int k = f[o];
	f[o] = ff(f[o]);
	s[o] += s[k], d[o] = d[f[o]];
	return f[o];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) f[i] = i, s[i] = 0, d[i] = 1;
	for (int i = 1; i <= n; i++) {
		char ch;
		int x, y;
		cin >> ch >> x >> y;
		int dx = ff(x), dy = ff(y);
		if (ch == 'M') {
			f[dx] = dy, s[dx] += d[dy], d[dx] += d[dy], d[dy] = d[dx];
		}
		if (ch == 'C') {
			if (dx != dy) {
				cout << "-1\n";
				continue;
			}
			cout << abs(s[x] - s[y]) - 1 << '\n';
		}
	}
	return 0;
}