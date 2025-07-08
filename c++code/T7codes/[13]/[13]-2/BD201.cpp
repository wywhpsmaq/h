#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z});
    }
    vector<long long> v(n + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    v[1] = 0;
    q.push({0, 1});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > v[u]) continue;
        for (auto& e : g[u]) {
            if (v[e.first] > v[u] + e.second) {
                v[e.first] = v[u] + e.second;
                q.push({v[e.first], e.first});
            }
        }
    }
    if (v[n] == LLONG_MAX) cout << -1;
    else cout << v[n];
    return 0;
}