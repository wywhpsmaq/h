#include <bits/stdc++.h>
using namespace std;
int dp[114514], v[1145][1145], w[1145][1145], num[1145];
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> num[i];
		for (int j = 1; j <= num[i]; j++) { cin >> v[i][j] >> w[i][j]; }
	}
	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 0; j--) {
			for (int k = 1; k <= num[i]; k++) {
				if (j >= v[i][k]) dp[j] = max (dp[j], dp[j - v[i][k]] + w[i][k]);
			}
		}
	}
	cout << dp[m];
}