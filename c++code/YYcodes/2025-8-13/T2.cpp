#include <bits/stdc++.h>
using namespace std;

int main () {
	int t;
	cin >> t;
	while (t--) {
		int a, b, c, num = 0;
		cin >> a >> b >> c;
		if (b >= a && b >= c) {
			num = min (max (b - a, b - c) + 1, b - 1);
			b -= num;
		}
		cout << num + ((a > b) ? 0 : b - a + 1) + ((c > b) ? 0 : b - c + 1) << '\n';
	}
}