#include <bits/stdc++.h>
using namespace std;
struct uu {
    int x, y, t;
    uu(int x, int y, int t) : x(x), y(y), t(t) {}
};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int sx, sy, ex, ey;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '@') {
                v[i][j] = 0;
            } else if (c == '#') {
                v[i][j] = -1;
                vis[i][j] = true;
            } else if (c == 'x') {
                v[i][j] = 2;
            } else if (c == 'r') {
                sx = i, sy = j;
                v[i][j] = 0;
            } else if (c == 'a') {
                ex = i, ey = j;
                v[i][j] = 0;
            }
        }
    }
    int ans = 0x3f3f3f3f;
    queue<uu> q;
    q.push(uu(sx, sy, 0));
    vis[sx][sy] = true;
    while (!q.empty()) {
        uu a = q.front();
        q.pop();
        int x = a.x, y = a.y;
        if (x == ex && y == ey) {
            ans = min(ans, a.t);
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny]) continue;
            if (v[nx][ny] == -1) continue;
            int nt = a.t + 1;
            if (v[nx][ny] == 2) nt++;
            if (nt >= ans) continue;
            vis[nx][ny] = true;
            q.push(uu(nx, ny, nt));
        }
    }
    if (ans == 0x3f3f3f3f){cout << "Impossible";}
    else{cout << ans;}
    return 0;
}