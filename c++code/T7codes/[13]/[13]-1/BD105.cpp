#include <bits/stdc++.h>
using namespace std;
int fa[114514];
int f(int x) {
    if (fa[x] != x) fa[x] = f(fa[x]);
    return fa[x];
}
void ff(int x, int y) {
    fa[f(x)] = f(y);
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        ff(u, v);
    }
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (f(a) == f(b)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}