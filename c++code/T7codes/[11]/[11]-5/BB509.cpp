#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, a;
    cin >> n >> m >> a;
    vector<vector<int>> p(m, vector<int>(n, 0));
    vector<vector<bool>> v(m, vector<bool>(n, false));
    vector<vector<int>> d(m, vector<int>(n, -1));
    queue<pair<int, int>> q;
    int sx = -1, sy = -1, ex = -1, ey = -1;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == '#') {
                p[i][j] = 0;
            } else if (c == '.') {
                p[i][j] = 1;
            } else if (c == 'S') {
                p[i][j] = 1;
                sx = i;
                sy = j;
            } else if (c == 'E') {
                p[i][j] = 1;
                ex = i;
                ey = j;
            }
        }
    }
    q.push({sx, sy});
    v[sx][sy] = true;
    d[sx][sy] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == ex && y == ey) {
            break;
        }
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && p[nx][ny] == 1 && !v[nx][ny]) {
                v[nx][ny] = true;
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    if (d[ex][ey] == -1) {
        cout << -1;
    } else {
        cout << a * d[ex][ey];
    }
    return 0;
}