// 单源最短路 - Dijkstra拉算法模版代码
#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 100005
#define inf 0x3f3f3f3f
vector<pair<int, int>> g[maxm]; // 使用vector存储图的邻接表
int dis[maxn];					// 存储最短路径
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int x, y, z; // x->y权值为z
		cin >> x >> y >> z;
		g[x].push_back (make_pair (y, z)); // 有向图
		// g[y].push_back(make_pair(x,z));//无向图
	}
	// 从1到n的最短路
	memset (dis, inf, sizeof (dis));
	dis[1] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // 优先队列-小根堆
	q.push (make_pair (0, 1)); // 第一个元素为距离，第二个元素为节点编号。表示1到1的最短距离为0
	while (!q.empty ()) {
        auto [d, u] = q.top(); // 获取当前最小距离的节点
        q.pop ();
        if (d > dis[u]) continue; // 如果当前距离大于了已经掌握的最优解，则跳过
        for (auto [v, w] : g[u]) { // 遍历当前节点的所有邻接节点
            if (dis[v] > dis[u] + w) { // 如果当前节点到邻接节点的距离小于已经掌握的最优解，则更新
                dis[v] = dis[u] + w;
                q.push (make_pair (dis[v], v)); // 将更新后的距离和节点编号加入优先队列
            }
        }
    }
    if(dis[n]==inf) cout<<"-1\n"; // 没有路径
    else cout<<dis[n]<<'\n';
    return 0;
}
/*
单源最短路 - Dijkstra 算法
时间复杂度：O((n+m)log n)
空间复杂度：O(n+m)
最大处理的数据范围：n<=1e5,m<=2e5
*/

