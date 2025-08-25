#include <bits/stdc++.h>
using namespace std;
double f[1 << 21][25], d[25][25], x[25], y[25];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        for (int j = 0; j < i; j++) {
            d[i][j] = d[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        }
    }
    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = DBL_MAX;
        }
    }
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        f[1 << (i - 1)][i] = d[0][i];
    }
    for (int i = 1; i < 1 << n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((i & 1 << (j - 1)) != 0) {
                const auto ii = i ^ 1 << (j - 1);
                for (int k = 1; k <= n; k++) {
                    if ((ii & 1 << (k - 1)) != 0) {
                        f[i][j] = min(f[i][j], f[ii][k] + d[k][j]);
                    }
                }
            }
        }
    }
    auto ans = DBL_MAX;
    for (int i = 1; i <= n; i++) {
        ans = min(f[(1 << n) - 1][i], ans);
    }
    printf("%.2f", ans);
}