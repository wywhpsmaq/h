#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	vector<pair<int, int>> v;
	cin >> n;
	for (int i = 0, x; i < n; i++) {
		cin >> x;
		v.emplace_back(x, 0);
	}
	sort(v.begin(), v.end());
	int l = 0, r = 1;
	for (; l < n; l++) {
		while (r < n && v[r] <= v[l] && !v[r].second) r++;
		if (r == n) {
			cout << n - l;
			return 0;
		}
		v[r].second = 1;
		r++;
	}
}
