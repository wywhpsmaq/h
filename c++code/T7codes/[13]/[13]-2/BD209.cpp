#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> m;
    vector<vector<pair<int, int>>> g(1000 + 1);
    int yy[114514] = {};
    for (int i = 0; i < m; ++i) {
        char a, b;
        int z;
        cin >> a >> b >> z;
        if (a < 'Z') yy[(int)a] = 1;
        if (b < 'Z') yy[(int)b] = 1;
        g[(int)a].push_back({(int)b, z});
        g[(int)b].push_back({(int)a, z});
    }
    vector<long long> v(125 + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    v[(int)'Z'] = 0;
    q.push({0, (int)'Z'});
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
    int ans = 111114514, num = 0;
    for (int i = 65; i <= 90; i++) {
        if (yy[i] == 1) {
            if (v[i] < ans) {
                ans = v[i];
                num = i;
            }
        }
    }
    cout << (char)num << " " << ans;
    return 0;
}