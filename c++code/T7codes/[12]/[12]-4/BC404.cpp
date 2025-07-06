#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> g[114514];
long long num = LLONG_MAX;
int n, m;
int d[114514], c[114514];
bool vi[114514];
int f() {
    queue<int> q;
    for (int i = 0; i <= n; ++i) {
        q.push(i);
        vi[i] = 1;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vi[u] = 0;
        for (auto e : g[u]) {
            int v = e.first, w = e.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                c[v] = c[u] + 1;
                if (c[v] > n + 1) return 0;
                if (!vi[v]) {
                    q.push(v);
                    vi[v] = 1;
                }
            }
        }
    }
    return 1;
}
int main() {
    int w;
    cin >> w;
    while (w--) {
        cin >> n >> m;
        for (int i = 0; i <= n; ++i) g[i].clear(), d[i] = 0, c[i] = 0, vi[i] = 0;
        for (int i = 0; i < m; ++i) {
            int l, r, v;
            cin >> l >> r >> v;
            g[l - 1].push_back({r, v});
            g[r].push_back({l - 1, -v});
        }
        if (f()) cout << "true\n";
        else cout << "false\n";
    }
    return 0;
}