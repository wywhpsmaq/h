#include <bits/stdc++.h>
using namespace std;
int sz[114514], ch[114514], n, q, fa[114514];
vector<int> t[114514], cc[114514];
void dfs(int u, int f) {
    sz[u] = 1;
    for (int v : t[u]) {
        if (v == f) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
void so(int u) {
    int c = u;
    while (true) {
        bool f = false;
        for (int v : t[c]) {
            if (v == fa[c]) continue;
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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
        t[fa[i]].push_back(i);
        t[i].push_back(fa[i]);
        cc[fa[i]].push_back(i);
    }
    dfs(1, 0);
    so(1);
    while (q--) {
        int x;
        cin >> x;
        cout << ch[x] << '\n';
    }
    return 0;
}