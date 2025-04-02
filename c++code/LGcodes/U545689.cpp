#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    int n = s.size();
    if (n == 0) {
        cout << 0;
        return 0;
    }
    
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++)
        isPal[i][i] = true;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j])
                isPal[i][j] = (j - i == 1) || isPal[i + 1][j - 1];
        }
    }
    
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++) {
        if (isPal[0][i])
            dp[i] = 0;
        else {
            dp[i] = i;
            for (int j = 0; j < i; j++) {
                if (isPal[j + 1][i])
                    dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    
    cout << dp[n-1];
    return 0;
}