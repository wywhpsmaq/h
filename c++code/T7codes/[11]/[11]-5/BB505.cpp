#include <bits/stdc++.h>
using namespace std;
int main() {
    struct uu {
        int x, y;
    };
    int n, m;
    cin >> n >> m;
    int s1, s2, e1, e2;
    vector<vector<pair<int, pair<int, int>>>> g(n, vector<pair<int, pair<int, int>>>(m));
    vector<vector<uu>> p(n, vector<uu>(m, {-1, -1}));
    vector<vector<bool>> v(n, vector<bool>(m, false));
    vector<vector<int>> ma(n, vector<int>(m));
    vector<uu> pa;
    queue<uu> q;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> ma[i][j];
        }
    }
    cin >> s1 >> s2 >> e1 >> e2;
    s1--, s2--, e1--, e2--;
    q.push({s1, s2});
    v[s1][s2] = true;
    bool f = false;
    while (!q.empty()) {
        uu c = q.front();
        q.pop();
        if (c.x == e1 && c.y == e2) {
            f = true;
            break;
        }
        for (int d = 0; d < 4; d++) {
            int nx = c.x + dx[d], ny = c.y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !v[nx][ny] && ma[nx][ny] == 0) {
                v[nx][ny] = true;
                p[nx][ny] = c;
                q.push({nx, ny});
            }
        }
    }
    if (!f) {
        cout << "no way";
        return 0;
    }
    uu c = {e1, e2};
    while (!(c.x == s1 && c.y == s2)) {
        pa.push_back(c);
        c = p[c.x][c.y];
    }
    pa.push_back({s1, s2});
    reverse(pa.begin(), pa.end());
    for (size_t i = 0; i < pa.size(); i++) {
        cout << "(" << pa[i].x + 1 << "," << pa[i].y + 1 << ")";
        if (i != pa.size() - 1) cout << "->";
    }
    return 0;
}