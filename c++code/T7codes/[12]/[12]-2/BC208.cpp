#include <bits/stdc++.h>
using namespace std;
int n, k, zj, num, aans;
int cut, h[114514], v[114514], et[114514];
int d[114514], f[114514], md[114514], ans[114514];
bool cmp(int a, int b) { return a > b; }
void dfs(int x, int fa) {
    if (d[x] > zj) {
        zj = d[x];
        num = x;
    }
    for (int i = h[x]; i; i = et[i]) {
        int y = v[i];
        if (y == fa) continue;
        d[y] = d[x] + 1;
        dfs(y, x);
    }
}
void dfs1(int x, int fa) {
    if (d[x] > zj) {
        zj = d[x];
        num = x;
    }
    for (int i = h[x]; i; i = et[i]) {
        int y = v[i];
        if (y == fa) continue;
        d[y] = d[x] + 1;
        f[y] = x;
        dfs1(y, x);
    }
}
void dfs2(int x, int fa) {
    md[x] = d[x];
    for (int i = h[x]; i; i = et[i]) {
        int y = v[i];
        if (y == fa) continue;
        d[y] = d[x] + 1;
        dfs2(y, x);
        md[x] = max(md[x], md[y]);
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[++cut] = y;
        et[cut] = h[x];
        h[x] = cut;
        v[++cut] = x;
        et[cut] = h[y];
        h[y] = cut;
    }
    dfs(1, 0);
    memset(d, 0, sizeof(d));
    zj = 0;
    dfs1(num, 0);
    int kkk = num;
    for (int i = 1; i <= (d[num] + 1) / 2; ++i) kkk = f[kkk];
    memset(d, 0, sizeof(d));
    dfs2(kkk, 0);
    for (int i = 1; i <= n; ++i) ans[i] = md[i] - d[i];
    sort(ans + 1, ans + n + 1, cmp);
    for (int i = k + 1; i <= n; ++i) aans = max(aans, ans[i] + 1);
    cout << aans;
    return 0;
}