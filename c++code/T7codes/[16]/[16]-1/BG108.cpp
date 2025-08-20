#include <bits/stdc++.h>
using namespace std;
struct uu {
	int x, y;
	bool operator< (const uu &b) const {
		return x < b.x;
	}
} a[210000];
int q[210000];
int n, m, h;
int main () {
	cin >> n;
	for (int i = 1; i <= n; ++i) { cin >> a[i].x >> a[i].y; }
	sort (a + 1, a + n + 1);
	h = 1;
	q[h] = a[1].y;
	for (int i = 1; i <= n; ++i) {
		if (a[i].y > q[h]) {
			h++;
			q[h] = a[i].y;
		} else if (a[i].y < q[h]) {
			int x = lower_bound (q + 1, q + h + 1, a[i].y) - q;
			q[x] = a[i].y;
		}
	}
	cout << h;
	return 0;
}