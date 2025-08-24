#include <bits/stdc++.h>
using namespace std;
int f[110][110];
int d[6][6] = {{0, 0, 0, 0, 0, 0},	   {0, 5, -1, -2, -1, -3}, {0, -1, 5, -3, -2, -4},
			   {0, -2, -3, 5, -2, -2}, {0, -1, -2, -2, 5, -1}, {0, -3, -4, -2, -1, 0}};
int main () {
	int la, lb, a[114], b[114];
	cin >> la;
	for (int i = 1; i <= la; i++) {
		char t;
		cin >> t;
		if (t == 'A') a[i] = 1;
		else if (t == 'C') a[i] = 2;
		else if (t == 'G') a[i] = 3;
		else if (t == 'T') a[i] = 4;
	}
	cin >> lb;
	for (int i = 1; i <= lb; i++) {
		char t;
		cin >> t;
		if (t == 'A') b[i] = 1;
		else if (t == 'C') b[i] = 2;
		else if (t == 'G') b[i] = 3;
		else if (t == 'T') b[i] = 4;
	}
	for (int i = 1; i <= la; i++) { f[i][0] = f[i - 1][0] + d[a[i]][5]; }
	for (int i = 1; i <= lb; i++) { f[0][i] = f[0][i - 1] + d[5][b[i]]; }
	for (int i = 1; i <= la; i++) {
		for (int j = 1; j <= lb; j++) { f[i][j] = max (f[i - 1][j - 1] + d[a[i]][b[j]], max (f[i - 1][j] + d[a[i]][5], f[i][j - 1] + d[5][b[j]])); }
	}
	cout << f[la][lb];
	return 0;
}
