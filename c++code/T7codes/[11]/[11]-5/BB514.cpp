#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> p(n + 2, vector<int>(m + 2, 0));
    vector<vector<int>> di(n + 2, vector<int>(m + 2, INT_MAX));
    vector<vector<bool>> v(n + 2, vector<bool>(m + 2, false));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> p[i][j];
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,greater<tuple<int, int, int>>>q;
    di[1][1] = p[1][1];
    q.emplace(di[1][1], 1, 1);
    while (!q.empty()) {
        auto [d, x, y] = q.top();
        q.pop();
        if (v[x][y]) continue;
        v[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
            if (!v[nx][ny] && di[nx][ny] > di[x][y] + p[nx][ny]) {
                di[nx][ny] = di[x][y] + p[nx][ny];
                q.emplace(di[nx][ny], nx, ny);
            }
        }
    }
    cout << di[n][m];
}