#include <bits/stdc++.h>
using namespace std;
long long ans[10000010];
int main () {
	int t, n;
	cin >> t >> n;
	for (int i = 1; i <= n; i++) {
		int v, w;
		cin >> v >> w;
		for (int j = v; j <= t; j++) { ans[j] = max (ans[j], ans[j - v] + w); }
	}
	cout << ans[t];
	return 0;
}