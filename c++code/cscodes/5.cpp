#include <bits/stdc++.h>
using namespace std;
int main () {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		switch (n % 7) {
		case 0: {
			while (n) {
				cout << 8;
				n -= 7;
			}
			break;
		}
		case 1: {
			cout << -1;
			break;
		}
		case 2: {
			cout << 1;
			n -= 2;
			while (n) {
				cout << 8;
				n -= 7;
			}
			break;
		}
		case 3: {
			cout << 7;
			n -= 3;
			while (n) {
				cout << 8;
				n -= 7;
			}
			break;
		}
		case 4: {
			cout << 4;
			n -= 4;
			while (n) {
				cout << 8;
				n -= 7;
			}
			break;
		}
		case 5: {
			cout << 2;
			n -= 5;
			while (n) {
				cout << 8;
				n -= 7;
			}
			break;
		}
		case 6: {
			cout << 6;
			n -= 6;
			while (n) {
				cout << 8;
				n -= 7;
			}
			break;
		}
		}
		cout << '\n';
	}
}
