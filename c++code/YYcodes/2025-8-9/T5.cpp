#include <bits/stdc++.h>
using namespace std;
#define int long long
int d[114514];
signed main () {
    ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a (n + 1);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += a[i];
	}
	while (m--) {
		int l, r;
		cin >> l >> r;
		d[l]++;
		if (r + 1 <= n) d[r + 1]--;
	}
	for (int i = 1; i <= n; i++) {
		d[i] += d[i - 1];
		if (a[i] % 2 && d[i] > 0) { ans++; }
	}
	cout << ans;
	return 0;
}