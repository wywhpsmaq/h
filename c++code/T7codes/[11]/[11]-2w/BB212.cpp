#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> g;
vector<pair<int, int>> ans;
int dx[4] = {1, 0};
int dy[4] = {0, 1};
bool vz[9999][9999];
int a, b;
int dfs(int x, int y) {
    if (x == a && y == b) {
        g.push_back(ans);
        return 0;
    }
    for (int i = 0; i < 2; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 1 && nx <= a && ny >= 1 && ny <= b && !vz[nx][ny]) {
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
    cin >> a >> b;
    vz[1][1] = 1;
    dfs(1, 1);
    for (int i = 0; i < g.size(); i++) {
        cout << i + 1 << ": 1,1";
        for (int j = 0; j < g[i].size(); j++) {
            cout << "->" << g[i][j].first << "," << g[i][j].second;
        }
        cout << endl;
    }
    return 0;
}