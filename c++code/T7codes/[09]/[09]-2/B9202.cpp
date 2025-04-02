#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    long long dp[9999] = {0};
    dp[0] = 1,dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % 100003;
    }
    cout << dp[n];
    return 0;
}
