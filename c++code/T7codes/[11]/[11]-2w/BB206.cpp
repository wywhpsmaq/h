#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> v, v1;
vector<vector<int>> p;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int ans = INT_MAX;
void dfs(int x, int y, int num) {
    if (x == 5 && y == 5) {
        if (ans > num) {
            ans = num;
            v1 = v;
        }
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= 5 && ny >= 1 && ny <= 5 && p[nx][ny] == 0) {
            p[nx][ny] = 1;
            v.push_back({nx, ny});
            dfs(nx, ny, num + 1);
            p[nx][ny] = 0;
        }
    }
}
int main() {
    p.resize(6, vector<int>(6));
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            cin >> p[i][j];
        }
    }
    p[1][1] = 1;
    v.push_back({1, 1});
    dfs(1, 1, 1);
    for (int i = 0; i < ans; i++) {
        cout << "(" << v1[i].first << ", " << v1[i].second << ")\n";
    }
}