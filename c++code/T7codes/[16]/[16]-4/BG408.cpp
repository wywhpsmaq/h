#include <bits/stdc++.h>
using namespace std;
int n, m, w[30], ans = INT_MIN;
int me(int x) {
    int cnt = 0;
    for (int i = 0; i <= n - 1; ++i)
        if (x & (1 << i)) cnt++;
    return cnt;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i <= n - 1; ++i) cin >> w[i];
    for (int i = 0; i <= (1 << n) - 1; ++i) {
        if (me(i) == n - m) {
            bitset<2010> b;
            b[0] = 1;
            for (int j = 0; j <= n - 1; ++j)
                if (i & (1 << j)) b = b | b << w[j];
            ans = max(ans, (int)b.count());
        }
    }
    cout << ans - 1;
    return 0;
}
