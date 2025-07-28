// 并查集算法模版代码
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000000
int n, m; // n为节点数，m为操作数
int fa[maxn]; // fa[i]表示i的父节点
int find (int x) { // 查找x的根节点
	if (fa[x] == x) return x; // 如果fa[x]是x本身，说明x是根节点
	else return fa[x] = find (fa[x]); // 路径压缩，直接将x的父节点设为根节点
}
void add (int x, int y) { // 合并x和y所在的集合
	int fx = find (x), fy = find (y);
	if (fx != fy) fa[fx] = fy; // 将x的根节点的父节点设为y的根节点
}
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i; // 初始化fa数组
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (x == 1) add (y, z); // 合并y和z所在的集合
		else if (x == 2) {
			if (find (y) == find (z)) cout << "Y\n"; // 如果y和z的根节点相同，说明它们在同一个集合中
			else cout << "N\n";  // 否则它们不在同一个集合中
		}
	}
}
/*
并查集算法模版
时间复杂度：O(n+m)
空间复杂度：O(n)
最大处理的数据范围：n<=1e5,m<=2e5
*/