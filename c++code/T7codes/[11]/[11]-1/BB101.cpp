#include<bits/stdc++.h>
using namespace std;
char c[110][110];
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
bool v[110][110];
int bx, by, ex, ey;
int n, k;

bool ch(int nx, int ny) {
    return nx >= 0 && nx < k && ny >= 0 && ny < k && c[nx][ny] == '.' && !v[nx][ny];
    return true;
}

bool dfs(int x, int y) {
    if (x == ex && y == ey) {
        return true;
    }
    v[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (ch(nx, ny)) {
            if (dfs(nx, ny)) return true;
        }
    }
    return false;
}

int main() {
    cin >> n;
    while (n--) {
        cin >> k;//迷宫大小
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                cin >> c[i][j];//迷宫
            }
        }
        cin >> bx >> by >> ex >> ey;//输入begin和end
        memset(v, false, sizeof(v));//赋初值
        if (c[bx][by] == '#' || c[ex][ey] == '#') {//特判
            cout << "NO\n";
            continue;
        }
        if (dfs(bx, by)) cout << "YES\n";//从begin开始
        else cout << "NO\n";
    }
}