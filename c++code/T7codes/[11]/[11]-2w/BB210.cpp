#include <bits/stdc++.h>
using namespace std;
int n, m;
int p[9999][9999];
bool v[9999][9999];
int px[] = {0, 1, 0, -1};
int py[] = {1, 0, -1, 0};
int dfs(int x, int y, int num) {
    if (num == n * m) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + px[i];
        int ny = y + py[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && v[nx][ny] == false) {
            p[nx][ny] = num + 1;
            v[nx][ny] = true;
            dfs(nx, ny, num + 1);
            return 0;
        }
    }
    return 0;
}
int main() {
    cin >> n >> m;
    p[1][1] = 1;
    v[1][1] = true;
    dfs(1, 1, 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << setw(3) << p[i][j];
        }
        cout << '\n';
    }
}
