#include <bits/stdc++.h>
using namespace std;
int p[510][510], v[510][510];
void print (int x, int y) {
	if (v[x][y] == 0) {
		cout << x << " " << y;
		return;
	}
	print (x, v[x][y]);
	cout << " " << v[x][y];
	print (v[x][y], y);
}
int main () {
	int n, m, q;
	cin >> n >> m >> q;
	memset (p, 0x3f3f3f3f, sizeof (p));
    for(int i = 1; i <= n; i++) 
        p[i][i] = 0;
	for(int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if(z < p[x][y]) {
            p[x][y] = z;
            v[x][y] = 0;
        }
    }
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (p[i][j] > p[i][k] + p[k][j]) {
					p[i][j] = p[i][k] + p[k][j];
					v[i][j] = k;
				}
			}
		}
	}
	while (q--) {
		int x, y;
		cin >> x >> y;
		if (p[x][y] == 0x3f3f3f3f) {
			cout << -1 << '\n';
		} else {
			cout << p[x][y] << " ";
			print (x, y);
			cout << '\n';
		}
	}
}