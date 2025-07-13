#include <bits/stdc++.h>
using namespace std;
vector<int> p[1145];
int a[1145], d[1145];
bool t[1145], f[1145][1145];
int main () {
	int n, m;
	cin >> n >> m;
	while (m--) {
		int x;
		cin >> x;
		memset (t, 0, sizeof (t));
		for (int i = 1; i <= x; ++i) {
			cin >> a[i];
			t[a[i]] = 1;
		}
		for (int i = a[1] + 1; i < a[x]; ++i) {
			if (t[i] == 0) {
				for (int j = 1; j <= x; ++j) {
					if (f[i][a[j]] == 0) {
						p[i].push_back (a[j]);
						d[a[j]]++;
						f[i][a[j]] = 1;
					}
				}
			}
		}
	}
	queue<pair<int, int>> q;
	for (int i = 1; i <= n; ++i) {
		if (!d[i]) q.push ({i, 1});
	}
	int ans = 0;
	while (!q.empty ()) {
		auto u = q.front ();
		q.pop ();
		ans = max (ans, u.second);
		for (auto i : p[u.first]) {
			d[i]--;
			if (d[i] == 0) { q.push ({i, u.second + 1}); }
		}
	}
	cout << ans;
	return 0;
}