#include<bits/stdc++.h>
using namespace std;
struct uu {
    long long a;
    int b;
    vector<int> v;
    uu() : a(LLONG_MAX), b(-1) {}
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<pair<int,int>>> p(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        p[u].push_back({v, w});
        p[v].push_back({u, w});
    }
    while (q--) {
        int s, t;
        cin >> s >> t;
        vector<uu> vv(n + 1);
        vector<bool> f(n + 1, false);
        queue<int> q;
        vv[s].a = 0;
        vv[s].v.push_back(s);
        q.push(s);
        f[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            f[u] = false;
            for (const auto& e : p[u]) {
                int v = e.first;
                long long x = vv[u].a + e.second;
                if (x < vv[v].a) {
                    vv[v].a = x;
                    vv[v].v = vv[u].v;
                    vv[v].v.push_back(v);
                    if (!f[v]) {
                        q.push(v);
                        f[v] = true;
                    }
                } else if (x == vv[v].a) {
                    vector<int> cc = vv[u].v;
                    cc.push_back(v);
                    if (cc < vv[v].v) {
                        vv[v].v = cc;
                        if (!f[v]) {
                            q.push(v);
                            f[v] = true;
                        }
                    }
                }
            }
        }
        if (vv[t].a == LLONG_MAX) {
            cout << -1 << '\n';
        } else {
            cout << vv[t].a;
            for (int x : vv[t].v) cout << ' ' << x;
            cout << '\n';
        }
    }
    return 0;
}