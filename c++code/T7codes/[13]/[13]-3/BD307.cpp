#include<bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n;
    vector<vector<pair<int, double>>> g(n + 1);
    vector<pair<int, int>> vv;
    vv.push_back({114514,114514});
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        vv.push_back({x,y});
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        double d = sqrt((vv[x].first - vv[y].first) * (vv[x].first - vv[y].first) + (vv[x].second - vv[y].second) * (vv[x].second - vv[y].second));
        g[x].push_back({y, d});
        g[y].push_back({x, d});
    }
    int ks, zz;
    cin >> ks >> zz;
    vector<double> v(n + 1, 0x3f3f3f);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    v[ks] = 0;
    q.push({0, ks});
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
    printf("%.2f", v[zz]);
    return 0;
}