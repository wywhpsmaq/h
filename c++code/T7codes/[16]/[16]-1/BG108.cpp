#include <bits/stdc++.h>
using namespace std;
struct uu {
	int x, y;
	bool operator< (const uu &b) const {
		return x < b.x;
	}
} a[210000];
int dp[210000];
int main () {
	int n, h;
	cin >> n;
	for (int i = 1; i <= n; ++i) { cin >> a[i].x >> a[i].y; }
	sort (a + 1, a + n + 1);
	h = 1;
	dp[h] = a[1].y;
	for (int i = 1; i <= n; ++i) {
		if (a[i].y > dp[h]) {
			h++;
			dp[h] = a[i].y;
		} else if (a[i].y < dp[h]) {
			int x = lower_bound (dp + 1, dp + h + 1, a[i].y) - dp;
			dp[x] = a[i].y;
		}
	}
	cout << h;
	return 0;
}