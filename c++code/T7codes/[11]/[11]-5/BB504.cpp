#include <bits/stdc++.h>
using namespace std;
int p[999][999];
bool v[999][999];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
struct uu {
    int x, y, d, t;
};
int vis[101][101][4];
int n, sx, sy, ex, ey;
int bfs() {
    int ans = 0x3f3f3f3f;
    queue<uu> q;
    q.push({sx, sy, -1, 0});
    memset(vis[sx][sy], 0, sizeof(vis[sx][sy]));
    while (!q.empty()) {
        auto [x, y, d, t] = q.front();
        q.pop();
        if (x == ex && y == ey) {
            ans = min(ans, t);
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || ny < 1 || nx > n || ny > n || p[nx][ny]) continue;
            int nt = t + (d != -1 && i != d);
            if (nt < vis[nx][ny][i]) {
                vis[nx][ny][i] = nt;
                q.push({nx, ny, i, nt});
            }
        }
    }
    return (ans == 0x3f3f3f3f) ? -1 : ans;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == 'A')
                sx = i, sy = j;
            else if (c == 'B')
                ex = i, ey = j;
            else if (c == 'x')
                p[i][j] = 1;
        }
    }
    memset(vis, 0x3f3f3f3f, sizeof(vis));
    int ans = bfs();
    cout << ans;
}