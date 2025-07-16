#include<bits/stdc++.h>
using namespace std;
struct uu {
    int zl, jz;
    double dj;
};
bool cmp(uu a, uu b) {
    return a.dj > b.dj;
}
int main() {
    uu p[114514];
    double n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i].zl = x, p[i].jz = y;
        p[i].dj = y / x;
    }
    sort(p, p + (int)n, cmp);
    int i = 0;
    double ans = 0;
    while (m != 0) {
        if (p[i].zl <= m) {
            ans += p[i].jz;
            m -= p[i].zl;
        } else {
            ans += p[i].dj * m;
            m = 0;
        }
        i++;
    }
    printf("%.2f", ans);
}