#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}
int main() {
	int n;
	vector<pair<int, int>> p;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back({x,y});
	}
	sort(p.begin(), p.end(), cmp);
	int ans = 0;
	bool a[114514] = {};
	for (int i = 0; i < n; i++) {
		bool f = 1;
		int num = 0;
		for (int j = p[i].first; j <= p[i].second; j++) {
			if (a[j]) {
				if (num) {
					f = 0;
					break;
				}
				num++;
			}
		}
		if (f) {
			for (int j = p[i].second; j >= p[i].first; j--) {
				if (!a[j]) {
					ans++;
					a[j] = 1;
					if (num) {
						break;
					}
					num++;
				}
			}
		}
	}
	cout << ans;
}