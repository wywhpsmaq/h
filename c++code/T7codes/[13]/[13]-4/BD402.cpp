#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> p(n + 1);
	vector<int> v(n + 1, 0);
	for (int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		p[x].push_back(y);
		//p[y].push_back(x);
		v[y]++;
	}
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 1; i <= n; ++i) {
		if (v[i] == 0) { q.push(i); }
	}
	vector<int> ans;
	while (!q.empty()) {
		int u = q.top();
		q.pop();
		ans.push_back(u);
		for (int i : p[u]) {
			v[i]--;
			if (v[i] == 0) q.push(i);
		}
	}
	if (ans.size() != n) {
		cout << -1 << '\n';
	} else {
		for (int i = 0; i < n; ++i) cout << ans[i] << " ";
	}
}