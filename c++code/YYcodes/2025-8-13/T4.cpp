#include <iostream>
using namespace std;
#define int unsigned int
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	int n, m, a, b, num = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a;
		num |= a;
	}
	int ans = 0;
	for (int i = 0; i < m; i++) {
		cin >> b;
		if ((b & num) == num) { ans++; }
	}
	cout << ans;
	return 0;
}