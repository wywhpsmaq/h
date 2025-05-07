#include <bits/stdc++.h>
using namespace std;
struct uu {
    int x, y, t;
    uu(int x_, int y_, int t_) : x(x_), y(y_), t(t_) {}
};
int n, m;
int p[110][110];
bool v[110][110];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int main() {
    cin >> n >> m;
    int sx, sy, ex, ey;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            p[i][j] = (c == '.') ? 0 : 1;
            if (c == 'S') {
                sx = i;
                sy = j;
                v[i][j] = 1;
                p[i][j] = 0;
            }
            if (c == 'T') {
                ex = i;
                ey = j;
                p[i][j] = 0;
            }
        }
    }
    queue<uu> q;
    q.push(uu(sx, sy, 0));
    while (!q.empty()) {
        uu a = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = a.x + dx[i];
            int ny = a.y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || p[nx][ny] == 1 || v[nx][ny]) continue;
            if (nx == ex && ny == ey) {
                cout << a.t + 1;
                return 0;
            }
            v[nx][ny] = 1;
            q.push(uu(nx, ny, a.t + 1));
        }
    }
    // cout<<-1;
    return 0;
}