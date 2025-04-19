#include<bits/stdc++.h>
using namespace std;
long long ff(long long a, long long k, vector<long long>& dp) {
    if (a == 0 || a == 1) {
        return 1;
    }
    if (dp[a] != -1) {
        return dp[a];
    }
    long long num = min(a, k);
    long long aas = 0;
    for (long long i = 1; i <= num; i++) {
        aas += ff(a - i, k, dp);
        aas %= 100003;
    }
    dp[a] = aas;
    return aas;
}
int main() {
    long long n, k;
    cin >> n >> k;
    vector<long long> dp(n + 1, -1);
    cout << ff(n, k, dp) % 100003;
    return 0;
}
