#include <bits/stdc++.h>
using namespace std;
int p[1000][1000];
int vis[1000][1000][4];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
struct uu {
    int x, y, d, t;
};
int n, m, sx, sy, ex, ey;
int bfs() {
    int ans = 0x3f3f3f3f;
    queue<uu> q;
    for (int i = 0; i < 4; i++) {
        vis[sx][sy][i] = 0;
        q.push({sx, sy, i, 0});
    }
    while (!q.empty()) {
        auto [x, y, d, t] = q.front();
        q.pop();
        if (x == ex && y == ey) {
            ans = min(ans, t);
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || p[nx][ny]) continue;
            int nt = t + (i != d);
            if (nt < vis[nx][ny][i]) {
                vis[nx][ny][i] = nt;
                q.push({nx, ny, i, nt});
            }
        }
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> p[i][j];
    cin >> sx >> sy >> ex >> ey;
    sx--, sy--, ex--, ey--;
    memset(vis, 0x3f, sizeof(vis));
    int ans = bfs();
    cout << ans;
    return 0;
}