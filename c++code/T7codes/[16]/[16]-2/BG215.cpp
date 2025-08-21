#include <bits/stdc++.h>
using namespace std;
int main () {
	string s;
	cin >> s;
	vector<vector<int>> dp ((int)s.size (), vector<int> ((int)s.size (), 0));
	for (int i = 2; i <= s.size (); i++) {
		for (int j = 0; j + i - 1 < s.size (); j++) {
			int k = j + i - 1;
			if (s[j] == s[k]) {
				dp[j][k] = dp[j + 1][k - 1];
			} else {
				dp[j][k] = min (dp[j + 1][k], dp[j][k - 1]) + 1;
			}
		}
	}
	cout << dp[0][s.size () - 1];
	return 0;
}