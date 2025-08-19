#include <bits/stdc++.h>
using namespace std;
int t;
string s;
long long dp[110][5000];
int main () {
	cin >> t;
	for (int i = 0; i < 26; i++) dp[1][i] = 1;
	for (int i = 2; i <= 100; i++) {
		dp[i][0] = 1;
		for (int j = 1; j <= 2700; j++) {
			for (int k = 0; k < 26; k++) {
				if (j - k >= 0) dp[i][j] = (dp[i][j] % 1000000007 + dp[i - 1][j - k] % 1000000007) % 1000000007;
			}
		}
	}
	while (t--) {
		cin >> s;
		int sum = 0;
		for (int i = 0; i < s.size (); i++) sum += s[i] - 'a';
		cout << dp[s.size ()][sum] % 1000000007 - 1 << endl;
	}
	return 0;
}
