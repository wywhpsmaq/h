#include<bits/stdc++.h>
using namespace std;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool v[999][999];
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > p(n, vector<int>(m));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> p[i][j];
        }
    }
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    queue<pair<int, int> > q;
    q.push({sx,sy});
    while (!q.empty()) {
        pair<int, int> a = q.front();
        int x = a.first, y = a.second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || p[nx][ny] == 1 || v[nx][ny]) continue;
            q.push({nx, ny});
        }
    }
}