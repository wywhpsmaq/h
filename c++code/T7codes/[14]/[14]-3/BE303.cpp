#include <bits/stdc++.h>
using namespace std;
int main () {
	int n;
	cin >> n;
	vector<pair<int, int>> p (n);
	vector<int> v;
	for (int i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
		for (int j = p[i].first; j <= p[i].second; j++) { v.push_back (j); }
	}
	sort (v.begin (), v.end ());
	v.erase (unique (v.begin (), v.end ()), v.end ());
	int ans = v.size ();
	for (int i = 0; i < v.size (); i++) {
		for (int j = i + 1; j < v.size (); j++) {
			vector<int> v_;
			v_.push_back (v[i]);
			v_.push_back (v[j]);
			for (int k = 0; k < n; k++) {
				int sum = 0;
				for (int o : v_) {
					if (o >= p[k].first && o <= p[k].second) { sum++; }
				}
				if (sum < 2) {
					for (int l = p[k].first; l <= p[k].second && sum < 2; l++) {
						if (find (v_.begin (), v_.end (), l) == v_.end ()) {
							v_.push_back (l);
							sum++;
						}
					}
				}
			}

			ans = min (ans, (int)v_.size ());
		}
	}
	cout << ans;
	return 0;
}