#include <bits/stdc++.h>
using namespace std;
struct uu {
    int v, n, w;
};
int d[114514], c[114514], q[114514], f[114514], h[114514], sum, ans = 0x7fffffff, n;
vector<uu> e(1);
int dfs(int u, int ff) {
    int t = 0;
    for (int i = h[u]; i != 0; i = e[i].n) {
        int v = e[i].v;
        if (v != ff) {
            int s = dfs(v, u);
            d[u] += d[v] + e[i].w * s;
            t += s;
        }
    }
    return q[u] = t + c[u];
}
void dfs2(int u, int ff) {
    for (int i = h[u]; i != 0; i = e[i].n) {
        int v = e[i].v;
        if (v != ff) {
            int ss = e[i].w;
            f[v] = f[u] - q[v] * ss + (sum - q[v]) * ss;
            dfs2(v, u);
        }
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; ++i) {
        sum += c[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({v, h[u], w});
        h[u] = e.size() - 1;
        e.push_back({u, h[v], w});
        h[v] = e.size() - 1;
    }
    dfs(1, 1);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, f[i]);
    }
    cout << ans + d[1];
    return 0;
}