#include <bits/stdc++.h>
using namespace std;
int a, b, ans = INT_MAX;
int p[999][999];
bool v[999][999];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
void dfs(int x, int y, int num) {
    if (x == a && y == b) {
        ans = min(num, ans);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= a && ny >= 1 && ny <= b && p[nx][ny] == 0) {
            v[nx][ny] = 1;
            dfs(nx, ny, num + 1);
            v[nx][ny] = 0;
        }
    }
}
int main() {
    cin >> a >> b;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            char c;
            cin >> c;
            if (c == '#') p[i][j] = 1;
        }
    }
    v[1][1] = true;
    dfs(1, 1, 1);
    cout << ans;
}