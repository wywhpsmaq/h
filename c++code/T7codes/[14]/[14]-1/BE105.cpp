#include <bits/stdc++.h>
using namespace std;
struct uu {
	int x, id;
};
struct d {
	int ans, pos;
} p[1000002];
int n, a[1000002], b[1000002], x, l;
unsigned long long ans;
inline int read () {
	int t = 0;
	char v = getchar ();
	while (v < '0') v = getchar ();
	while (v >= '0') {
		t = (t << 3) + (t << 1) + v - 48;
		v = getchar ();
	}
	return t;
}
inline bool cmp (d x, d y) {
	return x.ans > y.ans;
}
stack<uu> q;
int main () {
	n = read ();
	for (int i = 1; i <= n; ++i) a[i] = read ();
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) b[i] = read ();
	sort (b + 1, b + n + 1);
	l = 1;
	x = 1;
	while (1) {
		if (q.empty ()) {
			if (l <= n) x = a[l];
			else break;
		}
		while (a[l] == x) {
			q.push (uu{a[l], l});
			++l;
		}
		uu o = q.top ();
		q.pop ();
		p[o.id].ans = x - o.x;
		++x;
	}
	sort (p + 1, p + n + 1, cmp);
	for (int i = 1; i <= n; ++i) { ans += (unsigned long long)p[i].ans * b[i]; }
	cout << ans;
}