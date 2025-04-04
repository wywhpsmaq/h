#include<bits/stdc++.h>
using namespace std;
char p[1010][1010];
int id[1010][1010];
int s[1010*1010];
int cnt = 0;
int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, int cid) {
    id[x][y] = cid;
    s[cid]++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && !id[nx][ny]) {
            if (p[x][y] != p[nx][ny]) {
                dfs(nx, ny, cid);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!id[i][j]) {
                cnt++;
                dfs(i, j, cnt);
            }
        }
    }
    for (int q = 0; q < m; q++) {
        int i, j;
        cin >> i >> j;
        i--; j--;
        cout << s[id[i][j]] << '\n';
    }
    return 0;
}