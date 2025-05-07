#include<bits/stdc++.h>
using namespace std;
int n, m;
int num, ans;
bool zx[99];
bool zy[99];
struct uu {
    int x, y;
}p[9999];
int dfs(int x, int y, int nm, int o) {
    if (o == m + 1) {
        ans++;
        return 0;
    }
    for (int i = nm + 1; i <= num; i++) {
        if (!zx[p[i].x] && !zy[p[i].y]) {
            zx[p[i].x] = 1;
            zy[p[i].y] = 1;
            dfs(p[i].x, p[i].y, i, o + 1);
            zx[p[i].x] = 0;
            zy[p[i].y] = 0;
        }
    }
    return 0;
}
int main() {
    while (cin >> n >> m && n != -1 && m != -1) {
        memset(zx, false, sizeof(zx));
        memset(zy, false, sizeof(zy));
        ans = 0;
        num = 0;
        char c;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> c;
                if (c == '#') {
                    num++;
                    p[num].x = j, p[num].y = k;
                }
            }
        }
        dfs(p[0].x, p[0].y, 0, 1);
        cout << ans << '\n';
    }
}