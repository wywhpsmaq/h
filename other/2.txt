#include <bits/stdc++.h>
using namespace std;
int main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	int t;
	cin >> t;
	vector<vector<pair<int, int>>> mm;
	for (int i = 0; i < t; i++) {
		int n, m;
		cin >> n >> m;
		vector<pair<int, int>> v;
		if (n == 3) {
			v.push_back ({3, 2});
			v.push_back ({3, 2});
		} else if (n == 4) {
			v.push_back ({3, 4});
			v.push_back ({4, 2});
			v.push_back ({2, 4});
		} else {
			for (int i = 3; i < n; i++) { v.push_back ({i, n}); }
			int num = n;
			while (num > 2) {
				v.push_back ({n, 2});
				num = (num + 1) / 2;
			}
			v.push_back ({2, n});
		}
		mm.push_back (v);
	}
	for (auto i : mm) {
		cout << i.size () << "\n";
		for (auto p : i) { cout << p.first << " " << p.second << "\n"; }
	}
	return 0;
}