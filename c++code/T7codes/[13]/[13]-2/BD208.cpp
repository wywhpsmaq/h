#include<bits/stdc++.h>
using namespace std;
vector<long long> bfs(int s, const vector<vector<pair<int, int>>>& g) {
    int n = g.size() - 1;
    vector<long long> dist(n + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > dist[u]) continue;
        for (auto& e : g[u]) {
            if (dist[e.first] > dist[u] + e.second) {
                dist[e.first] = dist[u] + e.second;
                q.push({dist[e.first], e.first});
            }
        }
    }
    return dist;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z});
        rg[y].push_back({x, z});
    }
    vector<long long> to = bfs(k, g);
    vector<long long> f = bfs(k, rg);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (to[i] == LLONG_MAX || f[i] == LLONG_MAX) continue;
        ans = max(ans, to[i] + f[i]);
    }
    cout << ans;
    return 0;
}