#include<bits/stdc++.h>
using namespace std;
int p[510][510];
int v[510][510];
int main() {
    memset(p, 0x3f3f3f3f, sizeof p);
    int n, m, kk, q;
    cin >> n >> m >> q >> kk;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) v[i][j] = 1;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        p[x][y] =p[y][x]= min(p[x][y], z);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || j == k || i == k) continue;
                else if (p[i][k] + p[k][j] < p[i][j] && v[i][k] + v[k][j] < kk + 1) p[i][j] = p[i][k] + p[k][j], v[i][j] = v[i][k] + v[k][j];
            }
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (p[x][y] == 0x3f3f3f3f) cout << -1 << '\n';
        else cout << p[x][y] << '\n';
    }
}