#include <bits/stdc++.h>
using namespace std;
int n, m, p, x, y;
int fa[1000000];
int f(int x) {
    if (x == fa[x]) return x;
    return fa[x] = f(fa[x]);
}
void ff(int x, int y) {
    int f1 = f(x), f2 = f(y);
    if (f1 != f2) fa[f1] = f2;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        cin >> p >> x >> y;
        if (p == 1) ff(x, y);
        else {
            if (f(x) == f(y)) cout << "Y\n";
            else cout << "N\n";
        }
    }
}