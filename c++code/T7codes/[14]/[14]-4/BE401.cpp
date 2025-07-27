#include <bits/stdc++.h>
using namespace std;
int xx[200000], h[200000];
int main () {
	int a, t = 0;
	cin >> a;
	for (int i = 1; i <= a; i++) { cin >> xx[i] >> h[i]; }
	for (int i = 2; i <= a - 1; i++) {
		if (xx[i] - h[i] > xx[i - 1]) t++;
		else if (xx[i] + h[i] < xx[i + 1]) {
			t++;
			xx[i] += h[i];
		}
	}
	if (a == 1) cout << 1;
	else cout << t + 2;
}