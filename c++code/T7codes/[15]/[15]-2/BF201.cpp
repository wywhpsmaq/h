#include <bits/stdc++.h>
using namespace std;
long long ans[100010];
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int v, w, num;
		cin >> v >> w >> num;
		if (num == -1) {
			for (int j = m; j >= v; j--) { ans[j] = max (ans[j], ans[j - v] + w); }
		} else if (num == 0) {
			for (int j = v; j <= m; j++) { ans[j] = max (ans[j], ans[j - v] + w); }
		} else {
			for (int k = 1; k <= num; k = k * 2) {
				num -= k;
				for (int j = m; j >= k * v; j--) { ans[j] = max (ans[j], ans[j - k * v] + k * w); }
			}
			if (num)
				for (int j = m; j >= num * v; j--) { ans[j] = max (ans[j], ans[j - num * v] + num * w); }
		}
	}
	cout << ans[m];
}