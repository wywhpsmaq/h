#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    int t = 0;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        t = max(t, p[i]);
    }
    cout << t;
    vector<vector<vector<int>>> v(t + 10, vector<vector<int>>(n + 10, vector<int>(n + 10, 0x3f3f3f3f)));
    for (int o = 0; o <= t; ++o) {
        for (int i = 0; i < n; ++i) {
            v[o][i][i] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        int o = max(p[x], p[y]);
        for (int j = o; j <= t; ++j) {
            v[j][x][y] = (v[j][x][y] < z) ? v[j][x][y] : z;
            v[j][y][x] = (v[j][y][x] < z) ? v[j][y][x] : z;
        }
    }
    for (int o = 0; o <= t; ++o) {
        for (int k = 0; k < n; ++k) {
            if (p[k] > o) continue;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    v[o][i][j] = min(v[o][i][j], v[o][i][k] + v[o][k][j]);
                }
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        //if (z < p[x] || z < p[y]) cout << -1 << '\n';
        if (z > t) z = t;
        if (v[z][x][y] == 0x3f3f3f3f) cout << -1 << '\n';
        else cout << v[z][x][y] << '\n';
    }
    return 0;
}