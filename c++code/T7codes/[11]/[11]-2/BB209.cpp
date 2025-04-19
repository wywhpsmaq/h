#include<bits/stdc++.h>
using namespace std;
int p[999][999];
bool v[999][999];
int n;
bool check(int x, int y) {
    // 检查同一行的左侧是否有皇后
    for (int j = y - 1; j >= 1; --j) {
        if (p[x][j] == 0) break; // 遇到不可放置的位置就停止检查
        if (v[x][j]) return false; // 如果已有皇后，则不合法
    }

    // 检查同一行的右侧是否有皇后

    // 检查同一列的上方是否有皇后

    // 检查同一列的下方是否有皇后

    return true; // 所有检查都通过，可以放置皇后
}

void dfs(int now, int num) {
    // 边界条件：处理完所有格子（统计放置num个皇后的方案数）

    // 计算当前格子的坐标
    int x = (now - 1) / n + 1; // 行号
    int y = (now - 1) % n + 1; // 列号

    // 选择1：不在当前位置放置皇后
    dfs(now + 1, num);

    // 选择2：在当前位置放置皇后
    if (/*该位置可放置且不会攻击到其他皇后*/) {
        // 标记放置
        // 继续递归
        // 回溯，取消标记
    }
}
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }
    int ans = 0;

    cout << ans << '\n';
    return 0;
}