#include<bits/stdc++.h>
using namespace std;
int n, p;
int c[114], u[114], v[114], o[114];
int g[114][114];
int q[1145145];
int main() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> u[i];
        c[i] -= u[i];
    }
    for (int i = 1; i <= p; i++) {
        int x, y;
        cin >> x >> y;
        cin >> g[x][y];
        v[y]++;
        o[x]++;
    }
}