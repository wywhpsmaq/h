#include <bits/stdc++.h>
using namespace std;
int p[999][999];
bool v[999][999];
int n;
vector<int> ans;

bool check(int x, int y) {
    // 检查同一行的左侧是否有车
    for (int j = y - 1; j >= 1; --j) {
        if (p[x][j] == 0) break;   // 遇到洞就停止检查
        if (v[x][j]) return false; // 如果已有车，则不合法
    }

    // 检查同一行的右侧是否有车
    for (int j = y + 1; j <= n; ++j) {
        if (p[x][j] == 0) break;
        if (v[x][j]) return false;
    }

    // 检查同一列的上方是否有车
    for (int i = x - 1; i >= 1; --i) {
        if (p[i][y] == 0) break;
        if (v[i][y]) return false;
    }

    // 检查同一列的下方是否有车
    for (int i = x + 1; i <= n; ++i) {
        if (p[i][y] == 0) break;
        if (v[i][y]) return false;
    }

    return true; // 所有检查都通过，可以放置车
}

void dfs(int now, int num) {
    // 边界条件：处理完所有格子
    if (now > n * n) {
        ans[num]++;
        return;
    }

    // 计算当前格子的坐标
    int x = (now - 1) / n + 1; // 行号
    int y = (now - 1) % n + 1; // 列号

    // 选择1：不在当前位置放置车
    dfs(now + 1, num);

    // 选择2：在当前位置放置车
    if (p[x][y] == 1 && check(x, y)) {
        v[x][y] = true;        // 标记放置
        dfs(now + 1, num + 1); // 继续递归
        v[x][y] = false;       // 回溯，取消标记
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> p[i][j];
        }
    }

    ans.resize(n * n + 1, 0);
    dfs(1, 0);

    for (int i = 1; i <= n * n; i++) {
        if (ans[i] > 0) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}