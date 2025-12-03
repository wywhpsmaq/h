#include <bits/stdc++.h>
#define int long long
using namespace std;
using itn = int;
char a;
int n, q, b, pa, pb, pc;
struct uu {
	char lx;
	itn a;
};
vector<uu> v;
bool cmp (uu a, uu b) {
	if (a.lx != b.lx) {
		return a.lx < b.lx;
	} else {
		if (a.lx == 'A' || a.lx == 'C') {
			return a.a < b.a;
		} else if (a.lx == 'B') {
			return a.a > b.a;
		}
	}
}
int efd (char a, int b) {
	if (v[pa].a < b) return 0;
	if (a == 'B') return pa + 1;
	int l = (a == 'A' || a == 'B' ? (a == 'A') ? 0 : pa : pa + pb), r = (a == 'A' || a == 'B' ? (a == 'A') ? pa - 1 : pa + pb - 1 : n - 1);
	while (l < r) {
		int mid = (l + r) / 2;
		if (v[mid].a < b) l = mid + 1;
		else r = mid;
	}
	return l + 1;
}
int efx (char a, int b) {
	if (v[(a == 'A' ? 0 : pa + pb)].a >= b) return 0;
	if (a == 'A' || a == 'C') return (a == 'A' ? 1 : pa + pb + 1);
	int l = (a == 'A' || a == 'B' ? (a == 'A') ? 0 : pa : pa + pb), r = (a == 'A' || a == 'B' ? (a == 'A') ? pa - 1 : pa + pb - 1 : n - 1);
	while (l < r) {
		int mid = (l + r) / 2;
		if (v[mid].a > b) l = mid + 1;
		else r = mid;
	}
	return l + 1;
}
signed main () {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		pa += (a == 'A' ? 1 : 0), pb += (a == 'B' ? 1 : 0), pc += (a == 'C' ? 1 : 0);
		v.push_back ({a, b});
	}
	sort (v.begin (), v.end (), cmp);
	cin >> q;
	while (q--) {
		cin >> a >> b;
		if (b > 0) {
			cout << efd (a, b) << '\n';
		} else {
			cout << efx (a, -b) << '\n';
		}
	}
}