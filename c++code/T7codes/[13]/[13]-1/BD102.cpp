#include<bits/stdc++.h>
using namespace std;
vector<int> g[114514];
int ans[114514];
bool vis[114514];
void dfs(int u) {
    vis[u] = true;
    ans[u] = u;
    for (int v : g[u]) {
        if (!vis[v]) dfs(v);
        ans[u] = max(ans[u], ans[v]);
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i);
    }
    for (int i = 1; i <= n; ++i)  cout << ans[i] << " ";
    return 0;
}