// 最小生成树 - Kruskal算法模版代码
#include <bits/stdc++.h>
using namespace std;
namespace bcj { // 并查集,详解见F:\h\c++mb(template)\算法\并查集.cpp
int fa[100005];
int find (int x) {
	if (fa[x] == x) return x;
	else return fa[x] = find (fa[x]);
}
void add (int x, int y) {
	int fx = find (x), fy = find (y);
	if (fx != fy) fa[fx] = fy;
}
}
int n, m, p, x, y;
bool cmp (pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) { // 按权值升序排序
	return a.second.second < b.second.second;
}
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	vector<pair<int, pair<int, int>>> g;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) bcj::fa[i] = i;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y >> p;
		g.push_back ({x, {y, p}});
	}
	int ans = 0, num = 0;
	sort (g.begin (), g.end (), cmp);
	for (int i = 0; i < g.size (); i++) {
		int fx = bcj::find (g[i].first), fy = bcj::find (g[i].second.first);
		if (fx != fy) { // 如果x和y不在同一个集合中
			bcj::add (fx, fy); // 合并x和y所在的集合
			ans += g[i].second.second; // 累加权值
			num++; // 计数
		}
	}
	if (num == n - 1) cout << ans; // 如果边数等于n-1，说明是最小生成树
	else cout << "orz"; // 示无法构成最小生成树
}
/*
最小生成树 - Kruskal算法模版代码
时间复杂度：O(m log m)，其中m为边数
空间复杂度：O(m)，其中m为边数
最大处理的数据范围：n <= 1e5, m <= 2e5
*/