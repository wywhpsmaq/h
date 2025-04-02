#include<bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
vector<vector<char>> p;

bool dfs(int n, int x, int y, int nx, int ny) {
    if (p[x][y] == '#' || p[nx][ny] == '#') {
        return false;
    }
    vector<vector<bool>> v(n, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.push({x, y});
    v[x][y] = true;
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (x == nx && y == ny) {
            return true;
        }
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx >= 0 && xx < n && yy >= 0 && yy < n 
                && p[xx][yy] == '.' && !v[xx][yy]) {
                q.push({xx, yy});
                v[xx][yy] = true;
            }
        }
    }
    return false;
}
int main() {
    int k;
    cin >> k;
    while (k--) {
        int n;
        cin >> n;
        p.resize(n, vector<char>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> p[i][j];
            }
        }
        int ha, la, hb, lb;
        cin >> ha >> la >> hb >> lb;
        if (dfs(n, ha, la, hb, lb)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}