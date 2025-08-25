#include <bits/stdc++.h>
using namespace std;
int dp[114514];
int main() {
    vector<int> v;
    int x, n = 0;
    v.push_back(0);
    while (cin >> x) {
        v.push_back(x);
        n++;
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (v[j] > v[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    ans = 0;
    vector<int> p;
    for (int i = 1; i <= n; i++) {
        int num = INT_MAX, sum = -1;
        for (int j = 0; j < p.size(); j++) {
            if (p[j] > v[i] && p[j] < num) num = p[j], sum = j;
        }
        if (sum == -1) {
            p.push_back(v[i]);
            ans++;
        } else {
            p[sum] = v[i];
        }
    }
    cout << ans;
}