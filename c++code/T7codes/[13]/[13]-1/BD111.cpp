#include <bits/stdc++.h>
using namespace std;
int n, m;
int h[114514], e[114514], idx;
vector<pair<int, bool>> p[114514];
vector<int> v;
bool vis[114514];
int dfs(int x) {
	if (x == 1 && v.size() >= m + 1) {
		for (int i : v) { cout << i << " "; }
		exit(0);
	}
	for (auto& i : p[x]) {
		if (i.second == 0) {
			i.second = 1;
			v.push_back(i.first);
			for (auto& j : p[i.first]) {
				if (j.first == x) { j.second = 1; }
			}
			dfs(i.first);
			v.pop_back();
			i.second = 0;
			for (auto& j : p[i.first]) {
				if (j.first == x) { j.second = 0; }
			}
		}
	}
	return 0;
}
bool cmp(pair<int, bool> a, pair<int, bool> b) {
	return a.first > b.first;
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		p[x].push_back({y, 0});
		p[y].push_back({x, 0});
	}
	for (int i = 1; i <= n; i++) {
		if (p[i].size() != 0) {
			sort(p[i].begin(), p[i].end(), cmp);
		}
	}
	v.push_back(1);
	dfs(1);
}