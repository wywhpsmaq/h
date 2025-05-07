#include <bits/stdc++.h>
using namespace std;
int p[999][999];
bool v[999][999];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
struct Node { int x, y, dir, turns; };
int vis[101][101][4];
int n, sx, sy, ex, ey;
int bfs() {
    queue<Node> q;
    q.push({sx, sy, -1, 0});
    memset(vis[sx][sy], 0, sizeof(vis[sx][sy]));
    while(!q.empty()) {
        auto [x,y,dir,t] = q.front();
        q.pop();
        if(x == ex && y == ey) return t;
        for(int i=0; i<4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx<1||ny<1||nx>n||ny>n||p[nx][ny]) continue;
            int new_t = t + (dir != -1 && i != dir);
            if(dir != -1 && i == ((dir+2)%4)) continue;
            if(new_t < vis[nx][ny][i]) {
                vis[nx][ny][i] = new_t;
                q.push({nx, ny, i, new_t});
            }
        }
    }
    return -1;
}
int main() {
    cin >> n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++) {
            char c; cin >> c;
            if(c == 'A') sx=i, sy=j;
            else if(c == 'B') ex=i, ey=j;
            else if(c == 'x') p[i][j] = 1;
        }
    }
    memset(vis, 0x3f, sizeof vis);
    int ans = bfs();
    cout << (ans == -1 ? -1 : ans);
}