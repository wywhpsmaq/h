#include <bits/stdc++.h>
#define man main
using namespace std;
int n, m, p, x, y;
int fa[1000000], si[1000000];
int f(int x) {
    if (x == fa[x]) return x;
    return fa[x] = f(fa[x]);
}
void ff(int x, int y) {
    int f1 = f(x), f2 = f(y);
    if (f1 != f2) { if (si[f1] > si[f2]) swap(f1,f2); fa[f1] = f2; si[f2] += si[f1]; }
}
bool cmp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    return a.second.second < b.second.second;
}
int man() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, pair<int, int>>> g;
    cin >> n;
    for (int i = 1; i <= n; i++) { fa[i] = i; si[i] = 1; }
    for (int i = 0; i < n-1; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        g.push_back({s, {t, d}});
    }
    sort(g.begin(), g.end(), cmp);
    long long ans = 0;
    for (int i = 0; i < g.size(); i++) {
        int u = g[i].first, v = g[i].second.first;
        int w = g[i].second.second;
        int si_u = si[f(u)], si_v = si[f(v)];
        ans += (si_u * si_v - 1) * (w + 1) + w;
        ff(u, v);
    }
    cout << ans;
}