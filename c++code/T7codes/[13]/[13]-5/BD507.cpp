#include<bits/stdc++.h>
using namespace std;
struct uu {
    int u, v, c;
    bool operator<(const uu& other) const {
        return c < other.c;
    }
} p[10010];
int pa[310];
int f(int x) {
    return pa[x] == x ? x : pa[x] = f(pa[x]);
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> p[i].u >> p[i].v >> p[i].c;
    }
    sort(p, p + m);
    for (int i = 1; i <= n; i++)
        pa[i] = i;
    int aum = 0, ans = 0;
    for (int i = 0; i < m; i++) {
        int a = f(p[i].u);
        int b = f(p[i].v);
        if (a != b) {
            pa[a] = b;
            ans = p[i].c;
            if (++aum == n - 1) break;
        }
    }
    
    cout << n - 1 << " " << ans;
    return 0;
}