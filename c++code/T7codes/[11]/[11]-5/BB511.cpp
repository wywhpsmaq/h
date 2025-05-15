#include <bits/stdc++.h>
using namespace std;
int bfs(int sx, int sy) {
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dx_[4] = {-2, 2, 2, -2};
    int dy_[4] = {-2, -2, 2, 2};
    vector<vector<int>> ds(101, vector<int>(101, 0x3f3f3f3f));
    queue<pair<int, int>> q;
    ds[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        int d = ds[x][y];
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 1 && nx <= 100 && ny >= 1 && ny <= 100 && ds[nx][ny] > d + 1) {
                ds[nx][ny] = d + 1;
                q.push({nx, ny});
            }
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx_[i], ny = y + dy_[i];
            if (nx >= 1 && nx <= 100 && ny >= 1 && ny <= 100 && ds[nx][ny] > d + 1) {
                ds[nx][ny] = d + 1;
                q.push({nx, ny});
            }
        }
    }
    return ds[1][1];
}
int main() {
    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    cout << bfs(ax, ay) << '\n';
    cout << bfs(bx, by);
    return 0;
}