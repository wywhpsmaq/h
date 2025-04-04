#include <bits/stdc++.h>
using namespace std;
int h[1040][1040],h1[1040][1040];
int n, m;
int ans = 0,ans1 = 0,ans2 = 0;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs1(int x, int y) {
    h1[x][y] = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx > 0 && nx <= n && ny > 0 && ny <= m && h1[nx][ny] == 1) {
            dfs1(nx, ny);
        }
    }
    return;
}

int dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m || h[x][y] == 0) {
        return 0;
    }
    
    int area = 1;
    h[x][y] = 0;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        area += dfs(nx, ny);
    }
    return area;
}

int main() {
    cin >> n >> m;
    char c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            c=getchar();
            while (c == '\n' || c == ' ') {
                c = getchar();
            }
            if (c == '*') {
                h[i][j] = 1;
                h1[i][j] = 1;
                ans2++;
            }
            else {
                h[i][j] = 0;
                h1[i][j] = 0;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (h[i][j] == 1) {
                int num = dfs(i, j);
                ans = max(ans, num);
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if(h1[i][j] == 1) {
                ans1++;
                dfs1(i, j);
            }
        }
    }
    
    cout << ans1 << " " << ans2 << " " << ans;
    return 0;
}