#include <bits/stdc++.h>
using namespace std;

int main () {
	int a, b;
	cin >> a >> b;
	if (a > b) cout << 12 - a + b;
	else cout << b - a;
}