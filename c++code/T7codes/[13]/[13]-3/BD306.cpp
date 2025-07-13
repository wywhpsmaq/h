#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; j++) {
            int x;
            cin >> x;
            g[i].push_back({j,x});
            //g[j].push_back({i,x});
        }
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
    cout << v[n];
    return 0;
}