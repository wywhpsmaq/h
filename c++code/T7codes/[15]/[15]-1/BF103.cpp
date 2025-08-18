#include <bits/stdc++.h>
using namespace std;
long long ans[100010];
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int v, w, num;
		cin >> w >> v >> num;
		for (int k = 1; k <= num; k = k * 2) {
			num -= k;
			for (int j = m; j >= k * v; j--) { ans[j] = max (ans[j], ans[j - k * v] + k * w); }
		}
		if (num)
			for (int j = m; j >= num * v; j--) { ans[j] = max (ans[j], ans[j - num * v] + num * v); }
	}
	cout << ans[m];
}