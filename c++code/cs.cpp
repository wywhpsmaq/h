#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x].push_back({y, z});
    }
    vector<long long> v(n + 1, LLONG_MAX);
    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> q;
    v[1] = 0;
    int num = 1;
    q.push({0, {1,1}});
    while (!q.empty()) {
        if (num > k) break;
        auto [d, u] = q.top(); q.pop();
        if (u.second > k) break;
        if (d > v[u.first]) continue;
        for (auto& e : g[u.first]) {
            if (v[e.first] > v[u.first] + e.second) {
                v[e.first] = v[u.first] + e.second;
                q.push({v[e.first], {e.first,u.second + 1}});
                num++;
            }
        }
    }
    if (v[n] >= LLONG_MAX / 2) cout << "impossible";
    else cout << v[n];
    return 0;
}