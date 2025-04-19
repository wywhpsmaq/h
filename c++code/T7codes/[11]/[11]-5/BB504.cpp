#include<bits/stdc++.h>
using namespace std;
int p[9999][9999];
bool v[9999][9999];
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
int ans = INT_MAX, num = -1;
int n;
int sx, sy, ex, ey;
int dfs(int x, int y, int cx) {
    if (num > ans) return 0;
    if (x == ex && y == ey) {
        ans = min(ans, num);
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx<1 || ny<1 || nx>n || ny>n || p[nx][ny] == 1 || v[nx][ny]) {
            continue;
        } else {
            int nnn = (i + 2) % 4;
            int nn = num;
            num += (cx == i) ? 0 : (i == nnn) ? 2 : 1;
            v[nx][ny] = 1;
            dfs(nx, ny, i);
            v[nx][ny] = 0;
            num = nn;
        }
    }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c != '.') {
                if (c == 'A') {
                    sx = i, sy = j;
                } else if (c == 'B') {
                    ex = i, ey = j;
                } else p[i][j] = 1;
            } else p[i][j] = 0;
        }
    }
    v[sx][sy] = 1;
    dfs(sx, sy, -1);
    if (ans == INT_MAX) cout << -1;
    else cout << ans;
}