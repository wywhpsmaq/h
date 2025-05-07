#include<bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
vector<vector<char>> p;
void dfs(int x, int y) {
    int n = p.size();
    int m = p[0].size();
    
    queue<pair<int, int>> q;
    q.push({x, y});
    p[x][y] = '#';
    
    while (!q.empty()) {
        int px = q.front().first;
        int py = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = px + dx[i];
            int ny = py + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && p[nx][ny] == '0') {
                p[nx][ny] = '#';
                q.push({nx, ny});
            }
        }
    }
}
int main() {
    int x, y;
    cin >> x >> y;
    p.resize(x, vector<char>(y));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> p[i][j];
        }
    }
    for (int i = 0; i < x; i++) {
        if (p[i][0] == '0') dfs(i, 0);
        if (p[i][y-1] == '0') dfs(i, y-1);
    }
    for (int j = 0; j < y; j++) {
        if (p[0][j] == '0') dfs(0, j);
        if (p[x-1][j] == '0') dfs(x-1, j);
    }
    int ans = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (p[i][j] == '0') ans++;
        }
    }
    cout << ans <<'\n';
    return 0;
}