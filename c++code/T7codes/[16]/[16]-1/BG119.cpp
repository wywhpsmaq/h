#include <bits/stdc++.h>
using namespace std;
int a[200010], f[200010];
int main () {
	int n, l, r;
	cin >> n >> l >> r;
	for (int i = 0; i <= n; i++) { cin >> a[i]; }
	priority_queue<int> q1, q2;
	for (int i = 1; i < l; i++) { q2.push (a[i]); }
	for (int i = l; i <= n; i++) {
		q1.push (f[i - l]);
		if (i - r - 1 >= l) q2.push (f[i - r - 1]);
		while (!q2.empty () && q1.top () == q2.top ()) {
			q1.pop ();
			q2.pop ();
		}
		f[i] = q1.top () + a[i];
	}
	int ans = 0;
	for (int i = n - r + 1; i <= n; i++) { ans = max (ans, f[i]); }
	cout << ans;
}
