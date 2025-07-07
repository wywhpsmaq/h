#include<bits/stdc++.h>
using namespace std;
int n;
int zs[114514], rs[114514];
int p[114514];
int z(int a) {
    if (zs[a] != 0) z(zs[a]);
    cout << a << " ";
    if (rs[a] != 0) z(rs[a]);
    return 0;
}
int x(int a) {
    cout << a << " ";
    if (zs[a] != 0) x(zs[a]);
    if (rs[a] != 0) x(rs[a]);
    return 0;
}
int h(int a) {
    if (zs[a] != 0) h(zs[a]);
    if (rs[a] != 0) h(rs[a]);
    cout << a << " ";
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x >> zs[i] >> rs[i];
        p[zs[i]] = 1, p[rs[i]] = 1;
    }
    int xx;
    for (int i = 1; i <= n; i++) {
        if (p[i] != 1) {
            xx = i;
            break;
        }
    }
    x(xx);
    cout << '\n';
    z(xx);
    cout << '\n';
    h(xx);
}