#include <bits/stdc++.h>
using namespace std;
int ans[1100];
int a, b;
int main () {
	int n, t;
	cin >> n >> t;
	ans[0] = 1;
	for (int i = 0; i < n; i++) {
		cin >> a;
		for (int j = t; j >= a; j--) { ans[j] += ans[j - a]; }
	}
	cout << ans[t];
}