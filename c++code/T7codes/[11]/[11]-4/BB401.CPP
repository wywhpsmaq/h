#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
struct uu {
    bool f = 0;
    int x, y;
}p[9999];
int n;
double ans = 99999999;
double nd(double x1, double y1, double x2, double y2) {
    return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}
void dfs(int x, double num, int f) {
    if (num >= ans) return;
    if (x == n) {
        ans = (ans > num) ? num : ans;
        return;
    }
    for (int i = 0; i <= n; i++) {
        if (!p[i].f) {
            p[i].f = 1;
            dfs(x + 1, num + (nd(p[f].x, p[f].y, p[i].x, p[i].y)), i);
            p[i].f = 0;
        }
    }
}
int main() {
    cin >> n;
    p[0].x = 0, p[0].y = 0, p[0].f = 1;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    dfs(0, 0, 0);
    printf("%.2f", ans);
}