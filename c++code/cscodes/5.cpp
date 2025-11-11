#include <bits/stdc++.h>
using namespace std;
int main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	int t;
	cin >> t;
	while (t--) {
		int m;
		cin >> m;
		if (m == 1) {
			cout << "lose!\n";
			continue;
		}
		int l;
		if (m == 0) {
			l = 0;
		} else {
			long long num = 1 + 8l * m;
			double sum = sqrt (num);
			l = ceil ((1 + sum) / 2);
			while (1l * l * (l - 1) / 2 < m) { l++; }
			while (1l * (l - 1) * (l - 2) / 2 >= m) { l--; }
		}
		int r = 2 * m - 2;
		if (l > r) {
			cout << "lose!\n";
		} else {
			cout << l << " " << r << "\n";
		}
	}
	return 0;
}