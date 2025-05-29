#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> h;
vector<vector<int>> t;
vector<long long> sum, dp;
long long ans = LLONG_MAX;
void dfs1(int x, int fa) {
    sum[x] = h[x];
    for (int y : t[x]) {
        if (y == fa) continue;
        dfs1(y, x);
        sum[x] += sum[y];
        dp[x] += dp[y] + sum[y];
    }
}
void dfs2(int x, int fa) {
    ans = min(ans, dp[x]);
    for (int y : t[x]) {
        if (y == fa) continue;
        long long dx = dp[x], dy = dp[y];
        long long sx = sum[x], sy = sum[y];
        dp[x] -= dp[y] + sum[y], sum[x] -= sum[y], dp[y] += dp[x] + sum[x], sum[y] += sum[x];
        dfs2(y, x);
        dp[x] = dx, dp[y] = dy, sum[x] = sx, sum[y] = sy;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    t.resize(n + 1);
    h.resize(n + 1);
    sum.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        h[i] = a;
        if (b != 0) {
            t[i].push_back(b);
            t[b].push_back(i);
        }
        if (c != 0) {
            t[i].push_back(c);
            t[c].push_back(i);
        }
    }
    dfs1(1, 0);
    dfs2(1, 0);
    cout << ans;
}