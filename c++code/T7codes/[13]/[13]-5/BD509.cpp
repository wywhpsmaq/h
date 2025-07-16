#include<bits/stdc++.h>
using namespace std;
struct uu {
    int u, v, w;
    bool operator<(const uu& other) const {
        return w < other.w;
    }
};
int pa[2005];
int f(int x) {
    return pa[x] == x ? x : pa[x] = f(pa[x]);
}
bool ff(int a, int b) {
    a = f(a);
    b = f(b);
    if (a == b) return 0;
    pa[b] = a;
    return 1;
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<uu> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i].u >> p[i].v >> p[i].w;
    }
    sort(p.begin(), p.end());
    for (int i = 1; i <= n; ++i) pa[i] = i;
    int ans = 0, num = 0;
    for (auto e : p) {
        if (ff(e.u, e.v)) {
            ans = max(ans, e.w);
            if (++num == n - 1) break;
        }
    }
    cout << ans;
    return 0;
}