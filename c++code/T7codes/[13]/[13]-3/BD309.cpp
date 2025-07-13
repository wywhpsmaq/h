#include <bits/stdc++.h>
using namespace std;
int n, m, w, t;
vector<pair<int, pair<int, int>>> v;
bool f () {
    int v_[555];
	memset(v_, 0x3f, sizeof(v_));
    v_[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (auto &e : v) {
			if (v_[e.second.first] > v_[e.first] + e.second.second) {
				v_[e.second.first] = v_[e.first] + e.second.second;
				if (i == n) return true;
			}
		}
	}
	return false;
}
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cin >> t;
	while (t--) {
		cin >> n >> m >> w;
		v.clear ();
		for (int i = 0; i < m; ++i) {
			int x,y,z;
            cin>>x>>y>>z;
			v.push_back ({x, {y, z}});
			v.push_back ({y, {x, z}});
		}
		for (int i = 0; i < w; ++i) {
			int x,y,z;
            cin>>x>>y>>z;
			v.push_back ({x, {y, -z}});
		}
		if (f ()) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}