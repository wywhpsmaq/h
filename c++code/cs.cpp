#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
int n, m;
int ans[114514];
int nn = 0;
vector<int> p[114514];
vector<bool> v(114514);
void dfs(int x, int mm) {
    v[x] = 1;
    if (ans[x] == 0) ans[x] = mm, nn++;
    for (auto i : p[x]) {
        if (v[i] == 1) continue;
        dfs(i, x);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
    }
    for (int i = n; i >= 1; i--) {
        fill(v.begin(), v.begin() + n + 1, 0);
        dfs(i, i);
        if (nn == n) break;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
}