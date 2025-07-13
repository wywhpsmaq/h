#include <bits/stdc++.h>
using namespace std;
struct uu {
	int a, b, c, d;
};
// struct Point {
//     int x, y;
// };
int n;
vector<uu> v;
vector<pair<int, int>> vv;
vector<vector<int>> pv;
vector<int> v_;
vector<bool> vi;
bool p (int u) {
	for (int v : pv[u]) {
		if (!vi[v]) {
			vi[v] = true;
			if (v_[v] == -1 || p (v_[v])) {
				v_[v] = u;
				return true;
			}
		}
	}
	return false;
}
bool f (uu s, pair<int, int> p) {
	return p.first >= s.a && p.first <= s.b && p.second >= s.c && p.second <= s.d;
}
int main () {
	cin >> n;
	v.resize (n);
	vv.resize (n);
	pv.resize (n);
	for (int i = 0; i < n; i++) { cin >> v[i].a >> v[i].b >> v[i].c >> v[i].d; }
	for (int i = 0; i < n; i++) { cin >> vv[i].first >> vv[i].second; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (f (v[i], vv[j])) { pv[i].push_back (j); }
		}
	}
	v_.assign (n, -1);
	int num = 0;
	for (int i = 0; i < n; i++) {
		vi.assign (n, false);
		if (p (i)) num++;
	}
	if (num != n) {
		cout << "None";
		return 0;
	}
	vector<pair<char, int>> ans (n);
	for (int j = 0; j < n; j++) { ans[v_[j]] = {char ('A' + v_[j]), j + 1}; }
	sort (ans.begin (), ans.end ());
	for (auto p : ans) { cout << p.first << " " << p.second << '\n'; }
	return 0;
}