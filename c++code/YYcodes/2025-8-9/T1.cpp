#include <bits/stdc++.h>
using namespace std;
int main () {
	int n;
	cin >> n;
	for (int i = 1; i <= 9; i++) {
		if (i * 12 == n) {
			cout << i;
			return 0;
		}
	}
	cout << "404";
}