#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void countUpTo(ll n, vector<ll>& cnt) {
	cnt.assign(10, 0);
	if (n <= 0) return;
	for (ll factor = 1; factor <= n; factor *= 10) {
		ll lower = n % factor;
		ll cur = (n / factor) % 10;
		ll higher = n / (factor * 10);
		for (int d = 0; d <= 9; ++d) {
			if (d == 0) {
				if (higher == 0) continue;
				if (cur == 0) cnt[0] += (higher - 1) * factor + lower + 1;
				else cnt[0] += higher * factor;
			} else {
				if (cur < d) cnt[d] += higher * factor;
				else if (cur == d) cnt[d] += higher * factor + lower + 1;
				else cnt[d] += (higher + 1) * factor;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long a, b;
	while (cin >> a >> b) {
		if (a == 0 && b == 0) break;
		if (a > b) swap(a, b);
		vector<ll> cntB(10), cntA1(10);
		countUpTo(b, cntB);
		countUpTo(a - 1, cntA1);
		for (int i = 0; i <= 9; ++i) {
			ll ans = cntB[i] - cntA1[i];
			if (i) cout << ans;
			else cout << ans; // keep same formatting
			if (i != 9) cout << ' ';
		}
		cout << '\n';
	}
	return 0;
}
