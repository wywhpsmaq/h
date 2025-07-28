// 求有向图的拓扑序列模版代码
#include <bits/stdc++.h>
using namespace std;
int n, m;
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cin >> n >> m;
	vector<vector<int>> g (n + 1); // g[i]表示节点i的所有邻接点
	vector<int> in (n + 1); // in[i]表示节点i的入度
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back (y); // 有向图
		in[y]++; // 将y的入度加1
	}
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 1; i <= n; i++) {
		if (in[i] == 0) q.push (i); // 将入度为0的节点加入优先队列
	}
	vector<int> ans;
	while (!q.empty ()) {
		int x = q.top ();
		q.pop ();
		ans.push_back (x);
		for (int y : g[x]) // 遍历x的所有邻接点
		{
			in[y]--; // 将y的入度减1
			if (in[y] == 0) q.push (y); // 如果y的入度变为0，将其加入优先队列
		}
	}
	if (ans.size () != n) cout << -1; // 如果拓扑序列的长度不等于节点数，说明没有拓扑序列
	else {
		for (int x : ans) cout << x << " ";
	}
}
/*
有向图的拓扑序列模版
时间复杂度：O(n + m)
空间复杂度：O(n + m)
最大处理的数据范围：n <= 1e5, m <= 2e5
*/