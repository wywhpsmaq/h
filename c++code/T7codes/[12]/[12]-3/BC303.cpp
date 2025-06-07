#include<bits/stdc++.h>
using namespace std;
vector<int> p[114514];
int sz[114514];
int n, t;
void dfs(int u, int fa) {
    sz[u] = 1;
    for (int v : p[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
int f(int u, int fa) {
    for (int v : p[u]) {
        if (v == fa) continue;
        if (sz[v] > n / 2) return f(v, u);
    }
    return u;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            p[i].clear();
            sz[i] = 0;
        }
        vector<pair<int, int>> e;
        for (int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            p[x].push_back(y);
            p[y].push_back(x);
            e.push_back({x, y});
        }
        
        dfs(1, 0);
        int c = f(1, 0);
        int l = -1, pp = -1;
        for (int v : p[c]) {
            if (p[v].size() == 1) {
                l = v;
                pp = c;
                break;
            }
        }
        if (l == -1) {
            l = e[0].second;
            pp = e[0].first;
        }
        cout << pp << " " << l << '\n';
        bool ff = false;
        for (int v : p[l]) {
            if (v != pp) {
                cout << l << " " << v << '\n';
                ff = true;
                break;
            }
        }
        if (!ff) {
            cout << pp << " " << l << '\n';
        }
    }
    return 0;
}