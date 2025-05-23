#include <bits/stdc++.h>
using namespace std;
struct uu {
    int x, y, t;
    bool operator<(const uu &other) const { return t > other.t; }
};
char mp[30][30];
int vs[30][30];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int main() {
    int n, m;
    cin >> n >> m;
    memset(vs, 0x3f, sizeof(vs));
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
    priority_queue<uu> q;
    q.push({sx, sy, 0});
    vs[sx][sy] = 0;
    int ans = -1;
    while (!q.empty()) {
        auto [x, y, t] = q.top();
        q.pop();
        if (mp[x][y] == 'T') {
            ans = t;
            break;
        }
        if (t > vs[x][y]) continue;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (mp[nx][ny] == 'K') continue;
            int nt = t + (mp[nx][ny] == '#' ? 2 : 1);
            if (nt < vs[nx][ny]) {
                vs[nx][ny] = nt;
                q.push({nx, ny, nt});
            }
        }
    }
    cout << ans;
    return 0;
}