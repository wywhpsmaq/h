#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> e;
vector<vector<int>> p;
vector<bool> v;
int n;
void dfs(int u, vector<int> &c) {
    v[u] = true;
    c.push_back(u);
    for (int i : p[u]) {
        if (!v[i]) dfs(i, c);
    }
}
pair<int, int> bfs(int s) {
    vector<int> d(n + 1, -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    int f = s;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : p[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
                if (d[v] > d[f]) f = v;
            }
        }
    }
    return {f, d[f]};
}
int main() {
    cin >> n;
    e.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        e[i] = {a, b};
    }
    int ans = INT_MAX;
    for (int i = 0; i < n - 1; ++i) {
        vector<pair<int, int>> es;
        for (int j = 0; j < n - 1; ++j) {
            if (j != i) es.push_back(e[j]);
        }
        p.assign(n + 1, vector<int>());
        for (auto [a, b] : es) {
            p[a].push_back(b);
            p[b].push_back(a);
        }
        v.assign(n + 1, false);
        vector<int> c1;
        dfs(e[i].first, c1);
        for (int x : c1) v[x] = true;
        int o = -1;
        for (int j = 1; j <= n; ++j) {
            if (!v[j]) {
                o = j;
                break;
            }
        }
        v.assign(n + 1, false);
        vector<int> c2;
        dfs(o, c2);
        for (int u : c1) {
            for (int v : c2) {
                vector<pair<int, int>> ess = es;
                ess.push_back({u, v});
                p.assign(n + 1, vector<int>());
                for (auto &e : ess) {
                    p[e.first].push_back(e.second);
                    p[e.second].push_back(e.first);
                }
                auto p1 = bfs(1);
                auto p2 = bfs(p1.first);
                ans = min(ans, p2.second);
            }
        }
    }
    cout << ans;
    return 0;
}