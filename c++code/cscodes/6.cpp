#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll maxn (ll n, ll m) {
	if (m == 0) return n;
	ll l = 1, r = n;
	ll ans = n;
	while (l <= r) {
		ll mid = (l + r) / 2;
		ll v = mid * (2 * n - mid - 1);
		if (v >= 2 * m) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	return n - ans;
}
ll minn (ll n, ll m) {
	ll th = n * (n - 1) / 2;
	ll t = th - m;
	if (t <= 0) return 1;
	ll K = n * n - 2 * t;
	if (K < 0) return 1;
	ll px = sqrt (n);
	ll nr = n;
	for (ll q = 1; q <= px; ++q) {
		ll rn = (n + q) / (q + 1);
		ll rx = n / q;
		if (rn > rx) continue;
		ll num = n * (2 * q + 1) - K;
		ll gen = q * (q + 1);
		if (gen == 0) continue;
		ll r1 = (num + gen - 1) / gen;
		ll r2 = max (rn, r1);
		if (r2 <= rx && r2 < nr) { nr = r2; }
	}
	return nr;
}

int main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	int t;
	cin >> t;
	while (t--) {
		ll n, m;
		cin >> n >> m;
		cout << maxn (n, m) << " " << minn (n, m) << "\n";
	}
	return 0;
}
