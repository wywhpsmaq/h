#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> g;
vector<pair<int, int>> ans;
int dx[4] = {2, 1, -1, -2};
int dy[4] = {1, 2, 2, 1};
bool vz[9999][9999];
int a, b;
int dfs(int x, int y) {
    if (x == a && y == b) {
        g.push_back(ans);
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx <= a && ny >= 0 && ny <= b && !vz[nx][ny]) {
            vz[nx][ny] = 1;
            ans.push_back({nx, ny});
            dfs(nx, ny);
            ans.pop_back();
            vz[nx][ny] = 0;
        }
    }
    return 0;
}
int main() {
    a = 4, b = 8;
    ans.push_back({0, 0});
    vz[0][0] = 1;
    dfs(0, 0);
    for (int i = 0; i < g.size(); i++) {
        cout << i + 1 << ":";
        for (int j = 0; j < g[i].size(); j++) {
            if (j > 0) cout << "->";
            cout << g[i][j].first << "," << g[i][j].second;
        }
        cout << endl;
    }
    return 0;
}