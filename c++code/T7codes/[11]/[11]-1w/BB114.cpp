#include <bits/stdc++.h>
using namespace std;
int p[1040][1040];
int n, m;
int ans = 0;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m || p[x][y] == 0) {
        return 0;
    }
    
    int area = 1;
    p[x][y] = 0;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        area += dfs(nx, ny);
    }
    return area;
}

int main() {
    cin >> m >> n;
    char c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> c;
            p[i][j] = (c == '*') ? 1 : 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[i][j] == 1) {
                int num = dfs(i, j);
                ans = max(ans, num);
            }
        }
    }
    cout << ans;
    return 0;
}