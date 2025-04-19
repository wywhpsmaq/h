#include<bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
vector<vector<char>> p;
void dfs(int x, int y, int& num) {
    p[x][y] = '#';
    num++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < p.size() && ny >= 0 && ny < p[0].size() && (p[nx][ny] == '.' || p[nx][ny] == '@')) {
            dfs(nx, ny, num);
        }
    }
}
int main() {
    int w, h;
    while (cin >> w >> h && (w != 0 || h != 0)) {
        int sx = 0, sy = 0;
        p.assign(h, vector<char>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> p[i][j];
                if (p[i][j] == '@') {
                    sx = i;
                    sy = j;
                }
            }
        }
        int num = 0;
        dfs(sx, sy, num);
        cout << num << endl;
    }
    return 0;
}