#include <bits/stdc++.h>
using namespace std;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
vector<vector<int>> p;
int a, b;

void dfs(int x, int y, int num) {
    p[x][y] = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < a && ny >= 0 && ny < b && p[nx][ny] != 0) {
            dfs(nx, ny, num);
        }
    }
    return;
}
int main() {
    cin >> a >> b;
    char c;
    for (int i = 0; i < a; i++) {
        vector<int> v(b);
        for (int j = 0; j < b; j++) {
            cin >> c;
            v[j] = c - '0';
        }
        p.push_back(v);
    }
    int ans;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (p[i][j] != 0) {
                dfs(i, j, p[i][j]);
                ans++;
            }
        }
    }
    cout << ans;
}