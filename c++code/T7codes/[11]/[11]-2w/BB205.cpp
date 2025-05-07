#include <bits/stdc++.h>
using namespace std;
const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int n, m, sx, sy;
bool v[5][5];
int ans = 0;
bool ck(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && !v[x][y]; }
void dfs(int x, int y, int count) {
    if (count == n * m) {
        ans++;
        return;
    }
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (ck(nx, ny)) {
            v[nx][ny] = true;
            dfs(nx, ny, count + 1);
            v[nx][ny] = false;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> sx >> sy;
        ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                v[i][j] = false;
        v[sx][sy] = true;
        dfs(sx, sy, 1);
        cout << ans << endl;
    }
    return 0;
}