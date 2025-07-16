#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct uu {
    int u, v, w;
    bool operator<(const uu &e) const {
        return w > e.w;
    }
} p[N];
int n,m;
int pp[N], d[N];
vector<pair<int,int>> g[N];
int up[N][20], mu[N][20];
int ff(int u) {
    if (pp[u] != u)
        pp[u] = ff(pp[u]);
    return pp[u];
}
void f() {
    sort(p, p + m);
    for (int i = 1; i <= n; i++) pp[i] = i;
    
    for (int i = 0; i < m; i++) {
        int u = p[i].u, v = p[i].v, w = p[i].w;
        int pu = ff(u), pv = ff(v);
        if (pu != pv) {
            pp[pv] = pu;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
    }
}
void dfs(int u, int p, int w) {
    up[u][0] = p;
    mu[u][0] = w;
    d[u] = d[p] + 1;
    
    for (int i = 1; i < 20; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
        mu[u][i] = min(mu[u][i-1], mu[up[u][i-1]][i-1]);
    }
    
    for (auto [v, c] : g[u]) {
        if (v != p) dfs(v, u, c);
    }
}
int f_(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int ans = INT_MAX;
    for (int i = 19; i >= 0; i--) {
        if (d[u] - (1 << i) >= d[v]) {
            ans = min(ans, mu[u][i]);
            u = up[u][i];
        }
    }
    if (u == v) return ans;
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            ans = min({ans, mu[u][i], mu[v][i]});
            u = up[u][i];
            v = up[v][i];
        }
    }
    return min({ans, mu[u][0], mu[v][0]});
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> p[i].u >> p[i].v >> p[i].w;
    }
    f();
    for (int i = 1; i <= n; i++) {
        if (up[i][0] == 0) dfs(i, i, INT_MAX);
    }
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (ff(x) != ff(y)) {
            cout << -1 << endl;
        } else {
            cout << f_(x, y) << endl;
        }
    }
    return 0;
}