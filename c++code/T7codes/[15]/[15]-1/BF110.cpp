#include <bits/stdc++.h>
using namespace std;
long long ans[1000010];
int main () {
	int t, n;
	cin >> t >> n;
	for (int i = 1; i <= t; i++) {
		int v, w;
		cin >> w >> v;
		for (int j = v; j <= n * 3; j++) { ans[j] = max (ans[j], ans[j - v] + w); }
	}
	for (int i = 1;; i++) {
		if (ans[i] >= n) {
			cout << i;
			break;
		}
	}
}