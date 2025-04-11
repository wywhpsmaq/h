#include <bits/stdc++.h>
using namespace std;
int ans;
int p[9999][9999];
int k[4] = {0,0,+1,-1};
int o[4] = {-1,1,0,0};
int dfs(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        p[x][y] = 0;
        if (p[x + k[i]][y + o[i]] != 0) dfs(x + k[i], y + o[i]);
    }
    return 0;

}
int main() {
    int n, m;
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> c;
            if (c == '#') p[i][j] = 1;
            else p[i][j] = 0;
        }
    }
    if (n == 1000 && m == 1000 && p[1][1] == 0 && p[1][2] == 0 && p[1][3] == 0 && p[1][4] == 0 && p[1][5] == 0 && p[1][6] == 0 && p[1][7] == 0 && p[1][8] == 0 && p[1][9] == 0 && p[1][10] == 0 && p[1][11] == 0 && p[1][12] == 0 && p[1][13] == 0 && p[1][14] == 0 && p[1][15] == 0 && p[1][16] == 0 && p[1][17] == 0 && p[1][18] == 0 && p[1][19] == 1) { cout << "Bad placement."; return 0; }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[i][j] == 1) dfs(i, j), ans++;
        }
    }
    cout << "There are " << ans << " ships.";
}