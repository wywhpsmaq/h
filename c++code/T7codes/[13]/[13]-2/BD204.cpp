#include<bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') { f = -1; }ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
signed main() {
    int n, m;
    n = read(), m = read();
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int x = read(), y = read();
        g[x].push_back({y, 1});
        g[y].push_back({x, 1});
    }
    vector<int> ans(n + 1);
    ans[1] = 1;
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
                ans[e.first] = ans[u];
                q.push({v[e.first], e.first});
            } else if (v[e.first] == v[u] + e.second) {
                ans[e.first] += ans[u];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}