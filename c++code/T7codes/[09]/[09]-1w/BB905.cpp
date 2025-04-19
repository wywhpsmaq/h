#include <bits/stdc++.h>
using namespace std;
int main() {
	long long k;
	cin >> k;
	long long m = 0,n = 0,a = 0, b = 1;
	while (b <= k) {
		long long o = a + b;
		if (o > k) break;
		a = b;
		b = o;
	}
	if (b <= k) {
		m = a;
		n = b;
	}
	cout<<"m="<<m<<"\nn="<<n;
	return 0;
}