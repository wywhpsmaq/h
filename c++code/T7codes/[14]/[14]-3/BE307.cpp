#include <bits/stdc++.h>
using namespace std;
struct node {
	double x, y;
	bool vis = 0;
} a[1010];
bool cmp (node p, node q) {
	return p.y < q.y;
}
int main () {
	int n, d, ans;
	cin >> n >> d;
	for (register int i = 0; i < n; i++) {
		double p, q, m;
		cin >> p >> q;
		if (q > d) {
			cout << -1;
			return 0;
		}
		m = sqrt (d * d - q * q);
		a[i].x = p - m, a[i].y = p + m;
	}
	sort (a, a + n, cmp);
	for (int i = 0; i < n; i++) {
		if (a[i].vis) continue;
		ans++;
		a[i].vis = 1;
		for (int j = 0; j < n; j++){
			if (!a[j].vis && a[i].y >= a[j].x) a[j].vis = 1;
        }
	}
	cout << ans;
	return 0;
}