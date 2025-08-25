#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10, M = 1 << 16;
int m, n;
double dp[N][M];
struct node {
    int p, s;
} a[N];
int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        int tmp;
        cin >> a[i].p;
        while (cin >> tmp && tmp) a[i].s |= (1 << (tmp - 1));
    }
    for (int i = m; i >= 1; i--) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k = 1; k <= n; k++) {
                if ((j & a[k].s) == a[k].s)
                    dp[i][j] += max(dp[i + 1][j], dp[i + 1][j | (1 << (k - 1))] + a[k].p);
                else
                    dp[i][j] += dp[i + 1][j];
            }
            dp[i][j] /= n;
        }
    }
    printf("%.6f", dp[1][0]);
    return 0;
}