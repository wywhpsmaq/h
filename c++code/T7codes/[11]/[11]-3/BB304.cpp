#include<bits/stdc++.h>
using namespace std;
int dx[] = {0,0,0,1,-1,1,-1,1,-1};
int dy[] = {0,1,-1,0,0,1,-1,-1,1};
int p[999][999];
bool v[999][999];
int n, m;
int ans = 0;
bool ch(int x, int y) {
    for (int i = 0; i < 9; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (v[nx][ny]) return 0;
    }
    return 1;
}
void dfs(int x, int y, int num) {
    if (y == m + 1) x++, y = 1;
    if (x == n + 1 && y == 1) {
        ans = max(ans, num);
        return;
    }
    dfs(x, y + 1, num);
    if (ch(x, y)) {
        v[x][y] = 1;
        dfs(x, y + 1, num + p[x][y]);
        v[x][y] = 0;
    }
}
int main() {
    int a;
    cin >> a;
    for (int i = 0; i < a; i++) {
        ans = 0;
        cin >> n >> m;
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                cin >> p[j][k];
            }
        }
        dfs(1, 1, 0);
        cout << ans << '\n';
    }
}