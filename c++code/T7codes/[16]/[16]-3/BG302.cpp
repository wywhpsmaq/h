#include <bits/stdc++.h>
using namespace std;
int h[11451], v[11451];
vector<int> ez[11451];
int f[11451][2];
void dp (int x) {
	f[x][0] = 0;
	f[x][1] = h[x];
	for (int i = 0; i < ez[x].size (); i++) {
		int y = ez[x][i];
		dp (y);
		f[x][0] += max (f[y][0], f[y][1]);
		f[x][1] += f[y][0];
	}
}
int main () {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> h[i];
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		cin >> x >> y;
		ez[y].push_back (x);
		v[x] = 1;
	}
	int r;
	for (int i = 1; i <= n; i++)
		if (!v[i]) {
			r = i;
			break;
		}
	dp (r);
	cout << max (f[r][0], f[r][1]);
	return 0;
}
