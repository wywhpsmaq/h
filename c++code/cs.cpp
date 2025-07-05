#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int>> g[114514];
int n, m;
int dis[114514], cnt[114514];
bool vi[114514];
bool f() {
    fill(dis, dis + n + 2, 0);
    fill(cnt, cnt + n + 2, 0);
    fill(vi, vi + n + 2, false);
    queue<int> q;
    for (int i = 0; i <= n; ++i) {
        q.push(i);
        vi[i] = true;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vi[u] = false;
        for (auto &e : g[u]) {
            int v = e.first, w = e.second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n + 1) return false;
                if (!vi[v]) {
                    q.push(v);
                    vi[v] = true;
                }
            }
        }
    }
    return true;
}
int main() {
    int w;
    cin >> w;
    while (w--) {
        cin >> n >> m;
        for (int i = 0; i <= n; ++i) g[i].clear();
        for (int i = 0; i < m; ++i) {
            int l, r, v;
            cin >> l >> r >> v;
            g[l - 1].push_back({r, v});
            g[r].push_back({l - 1, -v});
        }
        if (f()) cout << "true\n";
        else cout << "false\n";
    }
    return 0;
}