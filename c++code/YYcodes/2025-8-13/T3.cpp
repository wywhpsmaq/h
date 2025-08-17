// 代码中"sb"的意思是"上班"，别瞎想！！！
#include <bits/stdc++.h>
using namespace std;
#define int long long
bool rn (int y) {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
int sbr (int y, int m, int d) {
	const int sbd[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
	int ans = 365 * (y - 1970);
	ans += (y - 1) / 4 - 1970 / 4;
	ans -= (y - 1) / 100 - 1970 / 100;
	ans += (y - 1) / 400 - 1970 / 400;
	ans += sbd[m - 1];
	if (m > 2 && rn (y)) ans++;
	ans += d;
	return ans;
}
int js (int a, int b, int c, int x, int y, int z) {
	int l = sbr (a, b, c);
	int r = sbr (x, y, z);
	if (l > r) { swap (a, x), swap (b, y), swap (c, z), swap (l, r); }
	int sb2 = (l - 1 + 4) % 7;
	int sbl = r - l + 1, fsb = sbl / 7, ans = fsb * 5;
	int rsb = sbl % 7;
	for (int i = 0; i < rsb; ++i) {
		int ss = (sb2 + i) % 7;
		if (ss == 3 || ss == 4 || ss == 5 || ss == 6 || ss == 0) { ans++; }
	}
	return ans;
}
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	int t;
	cin >> t;
	while (t--) {
		int a, b, c, x, y, z;
		cin >> a >> b >> c >> x >> y >> z;
		cout << js (a, b, c, x, y, z) << '\n';
	}
	return 0;
}