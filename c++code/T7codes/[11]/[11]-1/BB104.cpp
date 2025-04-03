#include<bits/stdc++.h>
using namespace std;
char p[9999][9999];
bool v[9999][9999];
int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int dfs(int x, int y) {
    v[x][y] = true;
    int ans = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !v[nx][ny]) {
            if (p[x][y] != p[nx][ny]) {
                ans += dfs(nx, ny);
            }
        }
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int q = 0; q < m; q++) {
        int i, j;
        cin >> i >> j;
        i--; j--;
        memset(v, false, sizeof(v));
        cout << dfs(i, j) << '\n';
    }
    return 0;
}