#include <bits/stdc++.h>
using namespace std;
int n, W, w[105], v[105], f[500][105], minn = INT_MAX, sum;
int main () {
	cin >> n >> W;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
		minn = min (minn, w[i]);
	}
	minn--;
	for (int i = 1; i <= n; i++) w[i] -= minn, sum += w[i];
	for (int i = 1; i <= n; i++) {
		for (int j = sum; j >= w[i]; j--) {
			for (int k = 1; k <= n; k++) {
				if (W < k * minn + w[i]) break;
				f[j][k] = max (f[j][k], f[j - w[i]][k - 1] + v[i]);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i < sum; i++)
		for (int j = 1; j <= n; j++) ans = max (ans, f[i][j]);
	cout << ans;
}