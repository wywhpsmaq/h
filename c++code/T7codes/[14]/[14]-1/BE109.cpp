#include <bits/stdc++.h>
using namespace std;
int main () {
	int n;
	cin >> n;
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++) {
		int t, w;
		cin >> t >> w;
		v.push_back ({t, w});
	}
	sort (v.begin (), v.end ());
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; i++) {
		if ((int)pq.size () < v[i].first) {
			pq.push (v[i].second);
		} else if (!pq.empty () && pq.top () < v[i].second) {
			pq.pop ();
			pq.push (v[i].second);
		}
	}
	int ans = 0;
	while (!pq.empty ()) {
		ans += pq.top ();
		pq.pop ();
	}
	cout << ans;
}