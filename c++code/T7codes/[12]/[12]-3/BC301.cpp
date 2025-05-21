#include <bits/stdc++.h>
using namespace std;
vector<int> t[10086];
int sz[10086];
int n;
int cd = 0, mt = 10086;
void dfs(int u, int parent) {
    sz[u] = 1;
    int ms = 0;
    for (int v : t[u]) {
        if (v == parent) continue;
        dfs(v, u);
        sz[u] += sz[v];
        ms = max(ms, sz[v]);
    }
    ms = max(ms, n - sz[u]);
    if (ms < mt || (ms == mt && u < cd)) {
        cd = u;
        mt = ms;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    dfs(1, 0);
    cout << cd << " " << mt;
    return 0;
}