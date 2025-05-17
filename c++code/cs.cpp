#include <bits/stdc++.h>
using namespace std;
struct uu {
    int to, w;
};
vector<uu> g[105];
int ans = 0, num = 0;
void dfs(int u, int fa, int dist) {
    bool f = true;
    for (auto &e : g[u]) {
        if (e.to != fa) {
            f = false;
            dfs(e.to, u, dist + e.w);
        }
    }
    if (f) {
        if (dist > ans) {
            ans = dist;
            num = 1;
        } else if (dist == ans) {
            num++;
        }
    }
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs(1, 0, 0);
    cout << ans << " " << num << endl;
    return 0;
}