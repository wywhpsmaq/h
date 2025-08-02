#include <bits/stdc++.h>
#include <windows.h>  // Windows 系统下设置控制台编码用
using namespace std;
int main() {
    SetConsoleOutputCP(65001);
    int n, m;
    int sx, sy, ex, ey;
    cin >> n >> m;
    cin >> sx >> sy >> ex >> ey;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;
            a[i][j] = (c == '1' ? 1 : 0);
        }
    }
    if (sx < 1 || sx > n || sy < 1 || sy > m || a[sx][sy] == 1 ||
        ex < 1 || ex > n || ey < 1 || ey > m || a[ex][ey] == 1) {
        cout << "999";
        return 0;
    }
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    vector<vector<pair<int, int>>> prev(n + 1, vector<pair<int, int>>(m + 1, {-1, -1}));
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;
    bool f = false;
    while (!q.empty() && !f) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m 
                && a[nx][ny] == 0 && !vis[nx][ny]) {
                vis[nx][ny] = true;
                prev[nx][ny] = {x, y};
                q.push({nx, ny});
                if (nx == ex && ny == ey) {
                    f = true;
                    break;
                }
            }
        }
    }
    if (f) {
        vector<pair<int, int>> path;
        for (pair<int, int> cur = {ex, ey}; cur != make_pair(-1, -1); cur = prev[cur.first][cur.second]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        pair<string, int> xdir = {"", 0};
        for (int i = 1; i < path.size(); ++i) {
            int sx = path[i-1].first;
            int sy = path[i-1].second;
            int xx = path[i].first;
            int xy = path[i].second;
            string dir;
            if (xx == sx - 1) dir = "上";
            else if (xx == sx + 1) dir = "下";
            else if (xy == sy - 1) dir = "左";
            else dir = "右";
            if (xdir.first == "") {
                xdir = {dir, 1};
            } else if (xdir.first == dir) {
                xdir.second++;
            } else {
                cout << xdir.first << " " << xdir.second << "; " ;
                xdir = {dir, 1};
            }
        }
        if (xdir.first != "") {
            cout << xdir.first << " " << xdir.second;
        }
    } else {
        cout << "666" ;
    }

    return 0;
}