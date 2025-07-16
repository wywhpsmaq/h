#include <bits/stdc++.h>
using namespace std;
int n;
int fa[100005];
int f(int x) {
    if (x == fa[x]) return x;
    return fa[x] = f(fa[x]);
}
void ff(int x, int y) {
    int f1 = f(x), f2 = f(y);
    if (f1 != f2) fa[f1] = f2;
}
struct uu {
    int u, v, w;
    bool operator<(const uu& rhs) const {
        return w < rhs.w;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<uu> e;
    for (int i = 1; i <= n; i++) fa[i] = i, fa[0] = 0;
    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        e.push_back({0, i, w});
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int p;
            cin >> p;
            if (i != j) e.push_back({i, j, p});
        }
    }
    sort(e.begin(), e.end());
    int ans = 0, cnt = 0;
    for (auto& e : e) {
        if (f(e.u) != f(e.v)) {
            ff(e.u, e.v);
            ans += e.w;
            cnt++;
            if (cnt == n) break;
        }
    }
    cout << ans;
}