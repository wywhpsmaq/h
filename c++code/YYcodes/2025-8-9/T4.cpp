#include <bits/stdc++.h>
using namespace std;
int main () {
	int n, m;
	cin >> n >> m;
	vector<int> v;
	v.push_back (0);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		v.push_back (x);
	}
	for (int i = 0; i < m; i++) {
		int x, a, b;
		cin >> x;
		if (x == 1) {
			cin >> a >> b;
			int ans = 0;
			for (int j = a; j <= b; j++) { ans = max (ans, v[j]); }
			cout << ans << '\n';
		} else if (x == 2) {
			cin >> a >> b;
			v.insert (v.begin () + a + 1, b);
		} else if (x == 3) {
			cin >> a >> b;
			v[a] = b;
		} else {
			cin >> a >> b;
			v.erase (v.begin () + a, v.begin () + b + 1);
		}
	}
}