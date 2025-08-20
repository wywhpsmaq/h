#include <bits/stdc++.h>
using namespace std;
int f[11][16], g[11][16], dp[11][16][11], n, m;
int main () {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
		}
	}
	memset (f, 0, sizeof (f));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= j; k++) {
				if (f[i][j] < f[i - 1][j - k] + g[i][k]) {
					f[i][j] = f[i - 1][j - k] + g[i][k];
					for (int h = 1; h < i; h++) dp[i][j][h] = dp[i - 1][j - k][h];
					dp[i][j][i] = k;
				}
			}
		}
	}
	cout << f[n][m] << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << " " << dp[n][m][i] << endl;
	}
}
