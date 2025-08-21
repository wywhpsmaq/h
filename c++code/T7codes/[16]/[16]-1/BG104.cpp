#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int a[114514], f1[114514], f2[114514], g[114514], l, ans = -inf;
int main () {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) { cin >> a[i]; }
	l = 0;
	for (int i = 1; i <= n; i++) {
		int num = lower_bound (g + 1, g + l + 1, a[i]) - g;
		f1[i] = num;
		g[num] = a[i];
		l = max (l, num);
	}
	l = 0;
	memset (g, 0, sizeof g);
	for (int i = n; i >= 1; i--) {
		int num = lower_bound (g + 1, g + l + 1, a[i]) - g;
		f2[i] = num;
		g[num] = a[i];
		l = max (l, num);
	}
	for (int i = 1; i <= n; i++) { ans = max (ans, f1[i] + f2[i] - 1); }
	cout << n - ans;
}
