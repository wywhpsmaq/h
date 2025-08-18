#include <bits/stdc++.h>
using namespace std;
int ans[110000];
int a, b;
int main () {
	int n, t;
	cin >> t >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		b *= a;
		for (int j = t; j >= a; j--) { ans[j] = max (ans[j], ans[j - a] + b); }
	}
	cout << ans[t];
}