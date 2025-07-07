#include<bits/stdc++.h>
using namespace std;
struct uu {
    int to;
    int w;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<uu>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z});
    }
    vector<long long> v(n + 1, 114514);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    v[1] = 0;
    q.push({0, 1});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > v[u]) continue;
        for (const auto& e : g[u]) {
            if (v[e.to] > v[u] + e.w) {
                v[e.to] = v[u] + e.w;
                q.push({v[e.to], e.to});
            }
        }
    }
    if (v[n] == 114514) cout << -1 << '\n';
    else cout << v[n] << '\n';
    return 0;
}