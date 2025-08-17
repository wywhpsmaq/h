#include <iostream>
using namespace std;
int main () {
	ios_base::sync_with_stdio (false);
	cin.tie (nullptr);
	int t;
	cin >> t;
	while (t--) {
		long long a, b, p;
		cin >> a >> b >> p;
		if (p == 1) {
			cout << "YES\n";
			continue;
		}
		if (b == 1) {
			if ((p - 1) % a == 0) cout << "YES\n";
			else cout << "NO\n";
		} else {
			long long num = 1;
			bool f = 0;
			while (num <= p) {
				long long r = p - num;
				if (r == 0) {
					f = 1;
					break;
				}
				if (r > 0 && r % a == 0) {
					f = 1;
					break;
				}
				if (num > p / b) break;
				num = num * b;
			}
			cout << (f ? "YES\n" : "NO\n");
		}
	}
}