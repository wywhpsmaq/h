#include<bits/stdc++.h>
using namespace std;
vector<long long> bfs(long long s, const vector<vector<pair<long long, long long>>>& g) {
    long long n = g.size() - 1;
    vector<long long> v(n + 1, LLONG_MAX);
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> q;
    v[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > v[u]) continue;
        for (auto e : g[u]) {
            if (v[e.first] > v[u] + e.second) {
                v[e.first] = v[u] + e.second;
                q.push({v[e.first], e.first});
            }
        }
    }
    return v;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long n, m;
    cin >> n >> m;
    vector<vector<pair<long long, long long>>> g(n + 1), rg(n + 1);
    for (long long i = 0; i < m; ++i) {
        long long x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z});
        rg[y].push_back({x, z});
    }
    vector<long long> to = bfs(1, g);
    vector<long long> f = bfs(1, rg);
    long long ans = 0;
    for (long long i = 1; i <= n; i++) {
        ans += to[i] + f[i];
    }
    cout << ans;
    return 0;
}