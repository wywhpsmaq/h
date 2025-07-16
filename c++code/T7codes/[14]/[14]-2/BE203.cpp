#include <bits/stdc++.h>
using namespace std;
int main () {
	int n, r;
	cin >> n >> r;
	vector<int> a (n + 1);
	for (int i = 1; i <= n; i++) { cin >> a[i]; }
	vector<int> fa (n + 1, 0);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		fa[b] = a;
	}
	fa[r] = 0;
	vector<int> num (n + 1, 1);
	vector<int> sum (n + 1);
	for (int i = 1; i <= n; i++) { sum[i] = a[i]; }
	vector<bool> vis (n + 1, false);
	int ans = 0;
	for (int i = 1; i <= n; i++) { ans += a[i]; }
	for (int k = 0; k < n - 1; k++) {
		int x = -1;
		double nsm = 0;
		for (int i = 1; i <= n; i++) {
			if (i == r || vis[i]) continue;
			double nnm = (double)sum[i] / num[i];
			if (x == -1 || nnm > nsm) {
				nsm = nnm;
				x = i;
			}
		}
		if (x == -1) break;
		int f = fa[x];
		while (f != 0 && vis[f]) { f = fa[f]; }
		ans += sum[x] * num[f], sum[f] += sum[x], num[f] += num[x];
		vis[x] = true;
		for (int i = 1; i <= n; i++) {
			if (fa[i] == x) { fa[i] = f; }
		}
	}
	cout << ans;
	return 0;
}