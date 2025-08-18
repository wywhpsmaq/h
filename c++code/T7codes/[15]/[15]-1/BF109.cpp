#include <bits/stdc++.h>
using namespace std;
int s, n, d;
int a[15], b[15];
int dp[1500000];
int main () {
	cin >> s >> n >> d;
	for (int i = 1; i <= d; i++) { cin >> a[i] >> b[i]; }
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= d; j++) {
			for (int k = a[j]; k <= s; k++) { dp[k] = max (dp[k], dp[k - a[j]] + b[j]); }
		}
		s += dp[s];
	}
	cout << s;
}