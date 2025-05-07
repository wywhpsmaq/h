#include <bits/stdc++.h>
using namespace std;
int p[9999][9999];
bool v[9999][9999];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int nnm, num, ans = -1;
int n, m;
int dfs(int x, int y) {
    if (p[x][y] == 4) nnm++;
    int nn = (p[x][y] == 4) ? 1 : p[x][y] + 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (p[nx][ny] == nn && v[nx][ny]) {
            ans = INT_MAX;
            return 0;
        }
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && p[nx][ny] == nn && !v[nx][ny]) {
            v[nx][ny] = true;
            dfs(nx, ny);
            if (ans == INT_MAX) return 0;
            num = max(num, nnm);
        }
    }
    return 0;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            p[i][j] = (c == 'L' || c == 'Q') ? (c == 'L') ? 1 : 2 : (c == 'B') ? 3 : 4;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[i][j] == 1) {
                memset(v, false, sizeof(v));
                nnm = 0;
                num = 0;
                dfs(i, j);
                ans = max(ans, num);
            }
        }
    }
    if (ans == INT_MAX) {
        cout << -1;
    } else
        cout << ans;
}