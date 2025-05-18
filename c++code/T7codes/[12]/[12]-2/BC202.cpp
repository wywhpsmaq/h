#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> p;
vector<pair<int, int>> ans;
vector<bool> v;
int num, r;
int n;
int dfs(int a, int sum) {
    if (sum > num) {
        num = sum, r = a;
    }
    for (auto [x, y] : p[a]) {
        if (!v[x]) {
            v[x] = true;
            dfs(x, sum + y);
        }
    }
    return 0;
}
int cz(int x, int a) {
    for (auto [b, c] : p[x]) {
        if (b == a) return c;
    }
    return 0;
}
int main() {
    cin >> n;
    p.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        p[a].push_back({b, c});
        p[b].push_back({a, c});
    }
    v.assign(n + 1, false);
    num = 0;
    v[1] = true;
    dfs(1, 0);
    int g_r = r;
    v.assign(n + 1, false);
    num = 0;
    v[g_r] = true;
    dfs(g_r, 0);
    int g_l = r;
    if (g_l > g_r) swap(g_l, g_r);
    ans.assign(n + 1, {0x3f3f3f3f, 0x3f3f3f3f});
    queue<pair<int, int>> q;
    vector<bool> vis(n + 1, false);
    q.push({g_l, 0});
    vis[g_l] = true;
    ans[g_l].first = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto [a, b] : p[x]) {
            if (!vis[a]) {
                vis[a] = true;
                ans[a].first = y + b;
                q.push({a, y + b});
            }
        }
    }
    fill(vis.begin(), vis.end(), false);
    q.push({g_r, 0});
    vis[g_r] = true;
    ans[g_r].second = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto [a, b] : p[x]) {
            if (!vis[a]) {
                vis[a] = true;
                ans[a].second = y + b;
                q.push({a, y + b});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d %d %d\n", i, ans[i].first, ans[i].second);
    }
    return 0;
}