#include <cmath>
#include <iostream>
using namespace std;
int f[114514], s[114514], b[114514];
int ff (int o) {
	if (f[o] == o) return o;
	int k = f[o];
	f[o] = ff (f[o]);
	s[o] += s[k];
	b[o] = b[f[o]];
	return f[o];
}
int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= 114513; i++) {
		f[i] = i,s[i] = 0,b[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		char ch;
		int x, y, dx, dy;
		cin >> ch >> x >> y;
		if (ch == 'M') {
			dx = ff (x);
			dy = ff (y);
			f[dx] = dy;
			s[dx] += b[dy],b[dx] += b[dy],b[dy] = b[dx];
		}
		if (ch == 'C') {
			dx = ff (x);
			dy = ff (y);
			if (dx != dy) {
				cout << -1 << '\n';
				continue;
			}
			cout << abs (s[x] - s[y]) - 1 << '\n';
		}
	}
	return 0;
}