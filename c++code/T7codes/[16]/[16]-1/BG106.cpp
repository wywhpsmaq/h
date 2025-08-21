#include <bits/stdc++.h>
using namespace std;
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	int n;
	cin >> n;
	vector<int> a (n), dp (n, 1), p (n, -1);
	for (int i = 0; i < n; ++i) { cin >> a[i]; }
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (a[j] < a[i]) {
				if (dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
					p[i] = j;
				} else if (dp[j] + 1 == dp[i] && j < p[i]) {
					p[i] = j;
				}
			}
		}
	}
	int ml = *max_element (dp.begin (), dp.end ()), e = -1;
	for (int i = 0; i < n; ++i) {
		if (dp[i] == ml) {
			if (e == -1 || i < e) { e = i; }
		}
	}
	vector<int> ans;
	while (e != -1) {
		ans.push_back (a[e]);
		e = p[e];
	}
	reverse (ans.begin (), ans.end ());
	cout << ml << '\n';
	for (int i = 0; i < ans.size (); ++i) {
		if (i > 0) cout << ' ';
		cout << ans[i];
	}
	return 0;
}