#include<bits/stdc++.h>
using namespace std;
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
        g[y].push_back({x,z});
    }
    bool vv[114514] = {};
    vector<int> v(n + 1, 0x3f3f3f);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    v[1] = 0;
    vv[1] = 1;
    q.push({0, 1});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > v[u]) continue;
        for (auto& e : g[u]) {
            if (v[e.first] > v[u] + e.second) {
                v[e.first] = v[u] + e.second;
                vv[e.first] = 1;
                q.push({v[e.first], e.first});
            }
        }
    }
    int ans = 0;
    bool f = 1;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, v[i]);
        if (!vv[i]) {
            f = 0;
            break;
        }
    }
    if (f) {
        cout << ans;
        return 0;
    }
    cout << -1;
    return 0;
}