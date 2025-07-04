#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g;
vector<pair<int, int>> ed;
int n;
pair<int, int> bfs(int s, const vector<vector<int>>& g) {
    vector<int> d(n + 1, -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    int fa = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
                if (d[v] > d[fa]) fa = v;
            }
        }
    }
    return {fa, d[fa]};
}
void dfs(int u, int fa, vector<int>& c, const vector<vector<int>>& g) {
    c.push_back(u);
    for (int v : g[u]) {
        if (v != fa) dfs(v, u, c, g);
    }
}
int main() {
    cin >> n;
    g.assign(n + 1, {});
    ed.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        ed[i] = {a, b};
    }
    int ans = INT_MAX;
    for (auto [a, b] : ed) {
        vector<vector<int>> g1 = g;
        g1[a].erase(find(g1[a].begin(), g1[a].end(), b));
        g1[b].erase(find(g1[b].begin(), g1[b].end(), a));
        vector<int> c1, c2;
        dfs(a, 0, c1, g1);
        dfs(b, 0, c2, g1);
        auto [u1, _] = bfs(c1[0], g1);
        auto [v1, d1] = bfs(u1, g1);
        auto [u2, __] = bfs(c2[0], g1);
        auto [v2, d2] = bfs(u2, g1); 
        int tp = max({(d1 + 1 + d2), d1, d2});
        ans = min(ans, tp);
    }
    cout << ans;
    return 0;
}