#include <bits/stdc++.h>
using namespace std;
struct uu {
    int x;
    vector<int> v;
} t[1001];
bool vis[1001];
void dfs(int x) {
    cout << t[x].x << " ";
    vis[x] = true;
    for (auto i : t[x].v) {
        if (!vis[i]) {
            dfs(i);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> t[i].x;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        t[x].v.push_back(y);
        t[y].v.push_back(x);
    }
    memset(vis, 0, sizeof(vis));
    dfs(1);
    return 0;
}