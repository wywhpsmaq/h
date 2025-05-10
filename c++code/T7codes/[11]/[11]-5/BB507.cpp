#include <bits/stdc++.h>
using namespace std;
struct uu {
    int x, y, t;
    uu(int x, int y, int t) : x(x), y(y), t(t) {}
};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    v[0][0] = 1;
    vis[0][0] = true;
    int num = 2;
    queue<uu> q;
    q.push(uu(0, 0, 1));
    while (!q.empty()) {
        uu a = q.front();
        q.pop();
        int x = a.x, y = a.y;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
                vis[nx][ny] = true;
                v[nx][ny] = num++;
                q.push(uu(nx, ny, num - 1));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << v[i][j] << " ";
        }
        cout << '\n';
    }
}