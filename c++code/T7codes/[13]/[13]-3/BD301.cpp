#include <bits/stdc++.h>
using namespace std;
int p[1145][1145], v[1145][1145];
void pp (int x, int y, vector<int> &p_) {
	if (v[x][y] == -1) return;
	pp (x, v[x][y], p_);
	p_.push_back (v[x][y]);
	pp (v[x][y], y, p_);
}
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) p[i][j] = 0;
			else p[i][j] = INT_MAX;
			v[i][j] = -1;
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (x == y) continue;
		if (p[x][y] > z) { p[x][y] = p[y][x] = z; }
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j || i == k || j == k) continue;
				if (p[i][k] == INT_MAX || p[k][j] == INT_MAX) continue;
				if (p[i][j] > p[i][k] + p[k][j]) {
					p[i][j] = p[i][k] + p[k][j];
					v[i][j] = k;
				} else if (p[i][j] == p[i][k] + p[k][j] && v[i][j] != -1 && k < v[i][j]) {
					v[i][j] = k;
				}
			}
		}
	}
	while (q--) {
		int x, y;
		cin >> x >> y;
		if (p[x][y] == INT_MAX) cout << -1 << '\n';
		else {
			cout << p[x][y] << " ";
			vector<int> P_;
			P_.push_back (x);
			pp (x, y, P_);
			P_.push_back (y);
			for (int i = 0; i < P_.size (); i++) {
				if (i == 0 || P_[i] != P_[i - 1]) cout << P_[i] << (i + 1 == P_.size () ? '\n' : ' ');
			}
		}
	}
}