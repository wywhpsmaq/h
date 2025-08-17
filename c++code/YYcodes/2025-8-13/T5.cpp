#include <bits/stdc++.h>
using namespace std;
int main () {
	int x, y;
	cin >> x >> y;
	vector<int> st (x + 1, 0);
	int f = 0;
	if (x <= 16) {
		vector<int> nums;
		for (int i = 1; i <= x; i++) nums.push_back (i);
		while (!nums.empty () && f < y) {
			int mid = nums.size () / 2;
			vector<int> o (8, 0);
			for (int i = 0; i < min (8, (int)nums.size () / 2); i++) { o[i] = nums[i]; }
			for (int i = 0; i < 8; i++) {
				if (i) cout << " ";
				cout << o[i];
			}
			cout.flush ();
			string s;
			cin >> s;
			if (s == "ok") return 0;
			int k;
			cin >> k;
			vector<int> l, r;
			for (int i = 0; i < mid; i++) l.push_back (nums[i]);
			for (int i = mid; i < nums.size (); i++) r.push_back (nums[i]);
			nums.clear ();
			if (k > 0) nums = l;
			if (f + k < y) nums.insert (nums.end (), r.begin (), r.end ());
			f += k;
		}
	} else {
		int bs = min (8, x / 2);
		vector<pair<int, int>> bk;
		for (int i = 1; i <= x; i += bs) { bk.push_back ({i, min (i + bs - 1, x)}); }
		for (auto [l, r] : bk) {
			if (f >= y) break;
			vector<int> o (8, 0);
			for (int i = 0, j = l; j <= r; i++, j++) { o[i] = j; }
			for (int i = 0; i < 8; i++) {
				if (i) cout << " ";
				cout << o[i];
			}
			cout.flush ();
			string s;
			cin >> s;
			if (s == "ok") return 0;
			int k;
			cin >> k;
			if (k == r - l + 1) {
				for (int i = l; i <= r; i++) st[i] = 1;
				f += k;
			}
		}
	}
	vector<int> ans (8, 0);
	int idx = 0;
	for (int i = 1; i <= x && idx < 8; i++) {
		if (st[i] == 1) ans[idx++] = i;
	}
	for (int i = 0; i < 8; i++) {
		if (i) cout << " ";
		cout << ans[i];
	}
	cout.flush ();
	string s;
	cin >> s;
	return 0;
}