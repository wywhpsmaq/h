#include <bits/stdc++.h>
using namespace std;
int sz[114514], ch[114514], n, q;
vector<vector<int>> cc;
vector<int> t[114514];
vector<int> p;
void dfs(int u, int fa);
void so(int u);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        t[p].push_back(i);
        t[i].push_back(p);
    }
    dfs(1, 0);
    p.resize(n + 1);
    cc.resize(n + 1);
    for (int i = 2; i <= n; ++i) {
        p[i] = 0;
        for (int v : t[i]) {
            if (v < i) p[i] = v;
        }
        cc[p[i]].push_back(i);
    }
    so(1);
    while (q--) {
        int x;
        cin >> x;
        cout << ch[x] << '\n';
    }
    return 0;
}
void so(int u) {
    int c = u;
    while (true) {
        bool f = false;
        for (int v : t[c]) {
            if (v == p[c]) continue;
            if (sz[v] > sz[u] / 2) {
                c = v;
                f = true;
                break;
            }
        }
        if (!f) break;
    }
    ch[u] = c;
    for (int v : cc[u]) {
        so(v);
    }
}
void dfs(int u, int fa) {
    sz[u] = 1;
    for (int v : t[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}