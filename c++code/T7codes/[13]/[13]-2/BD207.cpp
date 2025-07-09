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
    }
    vector<long long> v(n + 1, LLONG_MAX);
    priority_queue<pair<long long, pair<int, vector<int>>>, vector<pair<long long, pair<int, vector<int>>>>, greater<pair<long long, pair<int, vector<int>>>>> q;
    vector<int> o;
    o.push_back(1);
    v[1] = 0;
    q.push({0, {1,o}});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d > v[u.first]) continue;
        for (auto& e : g[u.first]) {
            if (v[e.first] > v[u.first] + e.second) {
                v[e.first] = v[u.first] + e.second;
                vector<int> oo = u.second;
                oo.push_back(e.first);
                q.push({v[e.first], {e.first,oo}});
                if (e.first == n) {
                    o = oo;
                }
            }
        }
    }
    if (v[n] == LLONG_MAX) cout << -1;
    else {
        cout << v[n] << '\n';
        for (int i = 0; i < o.size(); i++) {
            if (i) cout << "->";
            cout << o[i];
        }
    }
    return 0;
}