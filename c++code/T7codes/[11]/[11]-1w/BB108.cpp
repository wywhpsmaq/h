#include <bits/stdc++.h>
using namespace std;
int ans;
int n, m;
int p[999][999];
int k[] = {-1,1,0,0,1,-1,1,-1,0,2,0,-2};
int o[] = {0,0,1,-1,1,-1,-1,1,2,0,-2,0};
int dfs(int x, int y) {
    for (int i = 0; i < 12; ++i) {
        p[x][y] = 0;
        int nx = x + k[i];
        int ny = y + o[i];
        if (nx >= 1 && ny >= 1 && nx <= n && ny <= m && p[nx][ny] == 1) dfs(nx, ny);
    }
    return 0;

}
int main() {
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> c;
            if (c == '#') p[i][j] = 1;
            else p[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[i][j] == 1) dfs(i, j), ans++;
        }
    }
    cout << ans;
}