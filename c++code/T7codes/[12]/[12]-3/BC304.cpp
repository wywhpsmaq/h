#include <bits/stdc++.h>
using namespace std;
int f[10086], s[10086], d[10086];
int n, zx, sum = 0;
vector<int> g[10086];
queue<int> q;
void get(int u, int fa) {
    s[u] = 1, f[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        get(v, u);
        s[u] += s[v];
        f[u] = max(f[u], s[v]);
    }
    f[u] = max(f[u], n - s[u]);
    if (f[u] < f[zx] || (f[u] == f[zx] && u < zx)) zx = u;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f[0] = 0x3f3f3f3f;
    zx = 0;
    get(1, 0);
    q.push(zx);
    d[zx] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (d[v] || v == zx) continue;
            d[v] = d[u] + 1;
            sum += d[v] - 1;
            q.push(v);
        }
    }
    cout << zx << " " << sum;
}