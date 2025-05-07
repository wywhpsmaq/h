#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 1;
        return 0;
    }
    long long dp[1001];
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 3;
    for (int i = 3; i <= n; ++i) {
        dp[i] = (dp[i - 1] + 2 * dp[i - 2]) % 12345;
    }
    cout << dp[n];
}
