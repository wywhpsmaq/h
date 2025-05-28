#include <bits/stdc++.h>
using namespace std;
const int N = 300005;
int sz[N], ch[N], n, q, fa[N];
vector<int> t[N], cc[N];
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
        bool found = false;
        for (int v : t[c]) {
            if (v == fa[c]) continue;
            if (sz[v] > sz[u] / 2) {
                c = v;
                found = true;
                break;
            }
        }
        if (!found) break;
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