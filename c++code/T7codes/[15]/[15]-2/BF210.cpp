#include <iostream>
using namespace std;
int a[51], b[51], c[51];
int f[501][501];
int main () {
	int i, j, l, m, n, k;
	cin >> m >> n >> k;
	for (i = 1; i <= k; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
	for (i = 1; i <= k; i++) {
		for (j = m; j >= a[i]; j--) {
			for (l = n; l >= b[i]; l--) {
                f[j][l] = max (f[j][l], f[j - a[i]][l - b[i]] + c[i]);
            }
		}
	}
	cout << f[m][n];
	return 0;
}