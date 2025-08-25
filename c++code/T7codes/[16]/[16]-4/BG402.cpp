#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
int dp[15][114514];
bool f[114514];
signed main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m, n || m) {
        memset(dp, 0, sizeof dp);
        for (int i = 0; i < 1 << n; i++) {
            f[i] = true;
            int num = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {
                    if (num & 1) f[i] = false;
                    num = 0;

                } else {
                    num++;
                }
            }
            if (num & 1) f[i] = false;
        }
        dp[0][0] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < 1 << n; j++) {
                for (int k = 0; k < 1 << n; k++) {
                    if ((j & k) == 0 && f[j | k]) dp[i][j] += dp[i - 1][k];
                }
            }
        }
        cout << dp[m][0] << '\n';
    }
    return 0;
}