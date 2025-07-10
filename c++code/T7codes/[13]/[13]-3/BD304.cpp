#include<bits/stdc++.h>
using namespace std;
vector<int> ww[114514], ll[114514];
int n, m;
int bfs(int s, vector<int> graph[]) {
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                cnt++;
            }
        }
    }
    return cnt;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ww[a].push_back(b);
        ll[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int w = bfs(i, ww);
        int l = bfs(i, ll);
        if (w + l == n - 1) ans++;
    }
    cout << ans << endl;
    return 0;
}