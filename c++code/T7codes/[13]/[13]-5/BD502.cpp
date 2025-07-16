#include<bits/stdc++.h>
using namespace std;
int g[1145][1145];
int dis[114514];
bool v[114514];
int n, m;
int ff() {
    memset(dis, 0x3f3f3f3f, sizeof dis);
    dis[1] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x, mn = 0x3f3f3f3f;
        for (int j = 1; j <= n; j++) {
            if (v[j]) continue;
            if (dis[j] < mn) mn = dis[j], x = j;
        }
        if (dis[x] == 0x3f3f3f3f) cout << "orz";
        v[x] = 1;
        ans += dis[x];
        for (int j = 1; j <= n; j++) dis[x] = min(dis[x], g[i][x]);
    }
    cout << ans;
    return 0;
}
int main() {
    memset(g, 0x3f3f3f3f, sizeof g);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);
    }
    ff();
    return 0;
}