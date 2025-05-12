#include <bits/stdc++.h>
using namespace std;
int main() {
    struct uu {
        int x, y, t;
    };
    char mp[100][100];
    int vis[100][100];
    int n, m;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int ans = -1;
    queue<uu> q;
    cin >> n >> m;
    int sx = -1, sy = -1;
    for (int i = 0; i < n; ++i) {
        cin >> mp[i];
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }
    q.push({sx, sy, 0});
    vis[sx][sy] = 1;
    while (!q.empty()) {
        uu a = q.front();
        q.pop();
        if (mp[a.x][a.y] == 'T') {
            ans = a.t;
            break;
        }
        for (int d = 0; d < 4; ++d) {
            int nx = a.x + dx[d], ny = a.y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vis[nx][ny]) continue;
            if (mp[nx][ny] == 'K') continue;
            vis[nx][ny] = 1;
            if (mp[nx][ny] == '#') {
                q.push({nx, ny, a.t + 2});
            } else {
                q.push({nx, ny, a.t + 1});
            }
        }
    }
    cout << ans;
    return 0;
}