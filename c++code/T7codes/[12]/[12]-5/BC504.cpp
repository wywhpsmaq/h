#include<bits/stdc++.h>
using namespace std;
struct uu {
    int fa, ls, rs;
#define fa(i) t[i].fa
#define ls(i) t[i].ls
#define rs(i) t[i].rs
}t[10086];
int d[114514], d1[114514], d2[114514];
int ans = 0;
int dfs(int x, int l) {
    int num = l;
    num += d[x] + d1[x] + d2[x];
    ans += num;
    if (ls(x) != 0) dfs(ls(x), num);
    if (rs(x) != 0) dfs(rs(x), num);
    return 0;
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        ls(x) = y, rs(x) = z, fa(y) = x, fa(z) = x;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x == 1) d[y]++;
        else if (x == 2) d1[y]++;
        else d2[y]++;
    }
    dfs(1, 0);
    cout << ans;
}