#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<int, int>> p;
vector<vector<int>> g;
void dfs(int u, vector<bool> &vis, vector<int> &v) {
    vis[u] = true;
    v.push_back(u);
    for (int i : g[u]) {
        if (!vis[i]) dfs(i, vis, v);
    }
}
int main() {
    auto ks = [](const vector<pair<int, int>> &es) {
        g.assign(n + 1, vector<int>());
        for (auto &e : es) {
            g[e.first].push_back(e.second);
            g[e.second].push_back(e.first);
        }
    };
    function<void(int, vector<bool> &, vector<int> &)> dfs = [&](int u, vector<bool> &vis,
                                                                 vector<int> &v) {
        vis[u] = true;
        v.push_back(u);
        for (int i : g[u]) {
            if (!vis[i]) dfs(i, vis, v);
        }
    };
    auto f = [&](int x) {
        vector<bool> vis(n + 1, false);
        vector<int> v;
        dfs(x, vis, v);
        return v;
    };
    auto bfs = [](int x) {
        vector<int> d(n + 1, -1);
        queue<int> q;
        d[x] = 0;
        q.push(x);
        int far = x;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                    if (d[v] > d[far]) far = v;
                }
            }
        }
        return make_pair(far, d[far]);
    };
    cin >> n;
    p.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        p[i] = {a, b};
    }
    int ans = INT_MAX;
    for (int i = 0; i < n - 1; ++i) {
        vector<pair<int, int>> tp;
        for (int j = 0; j < n - 1; ++j) {
            if (j != i) tp.push_back(p[j]);
        }
        ks(tp);
        vector<int> v1 = f(p[i].first);
        vector<bool> vis(n + 1, false);
        for (int x : v1) vis[x] = true;
        int o = -1;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j]) {
                o = j;
                break;
            }
        }
        vector<int> v2 = f(o);
        for (int u : v1) {
            for (int v : v2) {
                vector<pair<int, int>> np = tp;
                np.push_back({u, v});
                ks(np);
                auto p1 = bfs(1);
                auto p2 = bfs(p1.first);
                int d = p2.second;
                ans = min(ans, d);
            }
        }
    }
    cout << ans;
    return 0;
}