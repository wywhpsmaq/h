#include<bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
int n;
char p[110][110];
int a = 1e9;
bool v[110][110][10];
void dfs(int x, int y, int fx, int num, pair<int,int>& e) {
    if(num >= a) return;
    if(x == e.first && y == e.second) {
        a = min(a, num);
        return;
    }
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && 
           p[nx][ny] != 'x' && !v[nx][ny][i]) {
            v[nx][ny][i] = true;
            int nnum = num + (i != fx && (x != nx || y != ny));
            dfs(nx, ny, i, nnum, e);
            v[nx][ny][i] = false;
        }
    }
}
int f(pair<int,int>& s, pair<int,int>& e) {
    a = 1e9;
    for(int fx = 0; fx < 4; fx++) {
        v[s.first][s.second][fx] = true;
        dfs(s.first, s.second, fx, 0, e);
        v[s.first][s.second][fx] = false;
    }
    return a == 1e9 ? -1 : a;
}
int main() {
    cin >> n;
    pair<int,int> s, e;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> p[i][j];
            if(p[i][j] == 'A') s = {i, j};
            if(p[i][j] == 'B') e = {i, j};
        }
    }
    cout << f(s, e);
    return 0;
}
