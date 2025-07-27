// 多源最短路 - Floyd算法模版代码
#include <bits/stdc++.h>
using namespace std;
#define maxn 505
#define maxm 505
#define inf 0x3f3f3f3f
int dis[maxn][maxn]; // 存储最短路径
int mid[maxn][maxn]; // 存储中间点或路径长度
void print (int st, int en) { // 输出路径
	if (mid[st][en] == 0) return;
	int k = mid[st][en];
	print (st, k);
	cout << k << " ";
	print (k, en);
}
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	int n, m, q, kk; // n个点，m条边，q次询问, kk为路径长度限制
	cin >> n >> m >> q; // 若果限边数，则输入kk
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) { dis[i][j] = inf, mid[i][j] = 0; } // 初始化,如果限制边数mid[i][j] = 1;
	}
	for (int i = 1; i <= n; ++i) dis[i][i] = 0;
	for (int i = 0; i < m; ++i) {
		int x, y, z; // x->y权值为z
		cin >> x >> y >> z;
		dis[x][y] = min (dis[x][y], z);
		dis[y][x] = min (dis[y][x], z); // 无向图
	}
	for (int k = 1; k <= n; ++k) { // 枚举中间点
		for (int i = 1; i <= n; ++i) { // 枚举起点
			for (int j = 1; j <= n; ++j) { // 枚举终点
                if (i == j || j == k || i == k) continue;// 避免自环
                /*如果不限制边数，就用以下条件*/
				else if (dis[i][j] > dis[i][k] + dis[k][j]) { // 更新最短路径
					dis[i][j] = dis[i][k] + dis[k][j];
					mid[i][j] = k; // 记录中间点
				}
                /*如果限制边数，就用以下条件*/
                // else if (dis[i][k] + dis[k][j] < dis[i][j] && mid[i][k] + mid[k][j] < kk + 1) dis[i][j] = dis[i][k] + dis[k][j], mid[i][j] = mid[i][k] + mid[k][j];
			}
		}
	}
	while (q--) {
		int x, y;
		cin >> x >> y;
		if (dis[x][y] == inf) cout << "-1\n"; // 没有路径
		else { // 输出最短路径长度和路径
			cout << dis[x][y] << " " << x << " ";
			print (x, y);
			if (x != y) cout << y; // 输出终点（避免自环重复）
			cout << '\n';
		}
	}
	return 0;
}
/*
多源最短路 - Floyd
时间复杂度：O(n^3)
空间复杂度：O(n^2)
最大处理的数据范围：n<=100
*/