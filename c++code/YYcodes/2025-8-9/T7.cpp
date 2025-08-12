#include <bits/stdc++.h>
using namespace std;
string s;
main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i){ cin >> a[i];}
    for (int i = 1; i <= n; ++i){ cin >> b[i];}
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
        auto r = unique(g[i].begin(), g[i].end());
        g[i].erase(r, g[i].end());
    }
    vector<vector<int>> fr(n + 1);
    vector<int> s(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        vector<int> v = g[i];
        sort(v.begin(), v.end(), [&](int x, int y) {
            return a[x] < a[y];
        });
        int sum = 0;
        vector<int> v1;
        for (int v : v) {
            if (sum + a[v] < a[i]) {
                sum += a[v];
                v1.push_back(v);
            } else {
                break;
            }
        }
        fr[i] = v1;
        s[i] = v1.size();
    }
    priority_queue<int, vector<int>, function<bool(int, int)>> pq([&](int x, int y) {
        return s[x] < s[y];
    });
    for (int u = 1; u <= n; ++u) {
        if (b[u] > 0) {
            pq.push(u);
        }
    }
    int ans = 0;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        if (b[u] == 0) continue;
        ans++;
        b[u]--;
        for (int v : fr[u]) {
            b[v]++;
            pq.push(v);
        }
    }
    cout << ans;
}