#include <bits/stdc++.h>
using namespace std;
int main () {
	int n, m;
	cin >> n >> m;
	vector<int> g[114];
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back (y);
		g[y].push_back (x);
	}
	int a;
	cin >> a;
	vector<int> v;
	for (int i = 0; i < a; i++) {
		int x;
		cin >> x;
		v.push_back (x);
	}
	vector<int> p;
	for (int i = 1; i < a; i++) { p[i] = p[i - 1] + v[i]; }
	int i = 0;
	int num = 1;
	while (num) {
		num += p[i];
		num /= v[i];
		i++;
		i %= a;
	}
	cout << num << " " << p[a - 1] - v[a - 1];
	return 0;
}