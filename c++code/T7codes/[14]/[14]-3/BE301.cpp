#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> m (1000005);
bool cmp (pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}
int main () {
	int n;cin >> n;
	for (int i = 0; i < n; i++) cin >> m[i].first >> m[i].second;
	sort (m.begin (), m.begin () + n, cmp);
	int num = 0;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (num <= m[i].first) {
			num = m[i].second;
			ans++;
		}
	}
    cout << ans;
	return 0;
}