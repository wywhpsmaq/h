#include<bits/stdc++.h>
using namespace std;
long long f(int a) {
    if (a <= 1) return a;
    vector<long long> dp(a + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= a; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            dp[i] += dp[j];
        }
        dp[i] += 1;
    }
    return dp[a];
}
int main() {
    int a;
    cin >> a;
    cout << f (a);
}
