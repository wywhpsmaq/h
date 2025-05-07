#include <bits/stdc++.h>
using namespace std;
char s[100][100];
bool vis[999][999];
bool v[999];
vector<char> v1, v2;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int ans = 1;
int n, m;

void dfs(int x, int y, int sum) {
    if (sum > ans) {
        ans = sum;
        v2 = v1;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && !v[s[nx][ny]]) {
            vis[nx][ny] = 1;
            v[s[nx][ny]] = 1;
            v1.push_back(s[nx][ny]);
            dfs(nx, ny, sum + 1);
            v1.pop_back();
            vis[nx][ny] = 0;
            v[s[nx][ny]] = 0;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> s[i][j];
        }
    }
    vis[1][1] = 1;
    v[s[1][1]] = 1;
    v1.push_back(s[1][1]);
    dfs(1, 1, 1);
    cout << ans << endl;
    for (auto c : v2) {
        cout << c << " ";
    }
    return 0;
}