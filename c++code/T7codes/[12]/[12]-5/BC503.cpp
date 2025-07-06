#include<bits/stdc++.h>
using namespace std;
int n;
int zs[114514], rs[114514];
int p[114514];
int ans;
int dfs(int x, int num) {
    if (zs[x] == 0 && rs[x] == 0) ans = max(ans, num);
    if (zs[x] != 0) dfs(zs[x], num + 1);
    if (rs[x] != 0) dfs(rs[x], num + 1);
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> zs[i] >> rs[i];
        p[zs[i]] = 1, p[rs[i]] = 1;
    }
    int xx;
    for (int i = 1; i <= n; i++) {
        if (p[i] != 1) {
            xx = i;
            break;
        }
    }
    dfs(xx, 1);
    cout << ans;
}