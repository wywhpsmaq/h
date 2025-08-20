#include <bits/stdc++.h>
using namespace std;
#define int long long
int num[114][114514], dp[114][114514];
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (0), cout.tie (0);
	string s;
	int v;
	cin >> s >> v;
	for (int i = 1; i <= s.size (); i++) {
		for (int j = i; j <= s.size (); j++) { num[i][j] = num[i][j - 1] * 10 + (s[j - 1] - '0'); }
	}
	memset (dp, 0x3f, sizeof (dp));
	dp[0][0] = -1;
	for (int i = 1; i <= s.size (); i++) {
		for (int k = 0; k <= v; k++) {
			for (int j = i - 1; j >= 0 && num[j + 1][i] <= v; j--) {
				if (k >= num[j + 1][i]) { dp[i][k] = min (dp[i][k], dp[j][k - num[j + 1][i]] + 1); }
			}
		}
	}
	if (dp[s.size ()][v] < 45) {
		cout << dp[s.size ()][v];
	} else cout << -1;
}