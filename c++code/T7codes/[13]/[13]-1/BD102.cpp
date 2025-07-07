#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, m, o;
vector<int>g[maxn];
bool vis[maxn];
void dfs(int x) {
    vis[x] = true;
    o = max(o, x);
    for (int y : g[x]) {
        if (!vis[y]) dfs(y);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        g[x].push_back(y);
    }
    for (int i = 1; i <= n; ++i) {
        o = i;
        dfs(i);
        cout << o << " ";
        memset(vis, false, sizeof(vis));
    }
    return 0;
}