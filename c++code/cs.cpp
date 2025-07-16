#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> p[114514];
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		p[x].push_back ({y, z});
	}
	vector<int> dis (n + 1, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push ({0, 1});
	dis[1] = 0;
	while (!q.empty ()) {
		auto x = q.top ();
		q.pop ();
		for (auto i : p[x.second]) {
			if (dis[i.first] > dis[x.second] + i.second) {
				dis[i.first] = dis[x.second] + i.second;
				q.push ({dis[i.first], i.first});
			}
		}
	}
	cout << dis[n];
}