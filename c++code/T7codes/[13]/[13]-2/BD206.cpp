#include<bits/stdc++.h>
#define N 114
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z});
        g[y].push_back({x, z});
    }
    int x, y;
    cin >> x >> y;
    vector<double> v(n + 1, 1e18);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    v[y] = 100;
    q.push({100, y});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > v[u]) continue;
        for (auto& e : g[u]) {
            if (e.first == y) continue;
            double ee = v[u] / (1.0 - e.second / 100.0);
            if (v[e.first] > ee) {
                v[e.first] = ee;
                q.push({v[e.first], e.first});
            }
        }
    }
    printf("%.8f", v[x]);
    return 0;
}