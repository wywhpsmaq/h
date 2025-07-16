#include <bits/stdc++.h>
using namespace std;
int n, m, p, x, y;
int fa[1000000];
int f(int x) {
	if (x == fa[x]) return x;
	return fa[x] = f(fa[x]);
}
void ff(int x, int y) {
	int f1 = f(x), f2 = f(y);
	if (f1 != f2) fa[f1] = f2;
}
bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
	return a.second.second < b.second.second;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int ans = 0;
	vector<pair<int, pair<int, int>>> g;
	cin >> n >> m;
    int num=1,sum=0;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> p;
        sum+=p;
		g.push_back({x,{y,p}});
	}
	sort(g.begin(), g.end(), cmp);
	for (int i = 0; i < g.size(); i++) {
		if (f(g[i].first) == f(g[i].second.first)) continue;
		else {
			ff(g[i].first, g[i].second.first);
			ans += g[i].second.second;
            num++;
		}
	}
    if(num!=n) cout<<"orz";
	else cout << sum-ans;
}