#include <bits/stdc++.h>
using namespace std;
struct uu {
    int x, y, t;
};
char mp[30][30];
bool vs[30][30];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int main() {
    int n, m;
    cin >> n >> m;
    memset(vs, 0, sizeof(vs));
    int sx = -1, sy = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mp[i][j];
            if (mp[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }
    queue<uu> q;
    q.push({sx, sy, 0});
    vs[sx][sy] = true;
    int ans = -1;
    while (!q.empty()) {
        auto [x, y, t] = q.front();
        q.pop();
        if (mp[x][y] == 'T') {
            ans = t;
            break;
        }
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vs[nx][ny] || mp[nx][ny] == 'K') continue;
            int nt = t;
            if (mp[nx][ny] == '#') {
                nt += 2;
            } else {
                nt += 1;
            }
            vs[nx][ny] = true;
            q.push({nx, ny, nt});
        }
    }
    cout << ans;
    return 0;
}