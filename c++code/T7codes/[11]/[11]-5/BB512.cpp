#include <bits/stdc++.h>
using namespace std;
int main() {
    struct uu {
        int x, y, t;
        uu(int a, int b, int c) : x(a), y(b), t(c) {}
    };
    int a;
    cin >> a;
    for (int i = 0; i < a; i++) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> p(n + 1, vector<int>(m + 1));
        vector<vector<bool>> v(n + 1, vector<bool>(m + 1));
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int sx, sy, ex, ey;
        queue<uu> q;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                char c;
                cin >> c;
                if (c == 'S') {
                    p[i][j] = 0;
                    v[i][j] = 1;
                    sx = i, sy = j;
                }
                if (c == 'E') {
                    p[i][j] = 0;
                    v[i][j] = 0;
                    ex = i, ey = j;
                } else
                    p[i][j] = (c == '.') ? 0 : 1;
            }
        }
        bool f = 1;
        q.push(uu(sx, sy, 0));
        while (!q.empty()) {
            auto [x, y, t] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx == ex && ny == ey) {
                    f = 0;
                    cout << t + 1 << '\n';
                    break;
                }
                if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
                if (v[nx][ny] || p[nx][ny] == 1) continue;
                q.push(uu(nx, ny, t + 1));
                v[nx][ny] = 1;
            }
            if (!f) break;
        }
        if (f) {
            cout << "oop!\n";
        }
    }
}