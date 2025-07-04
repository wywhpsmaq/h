#include <iostream>
#include <vector>
using namespace std;
vector<int> p;
int f (int x) {
	if (p[x] != x) p[x] = f (p[x]);
	return p[x];
}
void ff (int x, int y) {
	int fx = f (x), fy = f (y);
	if (fx != fy) p[fx] = fy;
}
int main () {
	int n, m;
	cin >> n >> m;
	vector<int> d (n + 1, 0);
	p.resize (n + 1);
	for (int i = 1; i <= n; ++i) p[i] = i;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		d[a]++,d[b]++;
		ff (a, b);
	}
	for (int i = 1; i <= n; ++i) {
		cout << d[i];
		if (i != n) cout << " ";
	}
	cout << '\n';
	int sum = 0, r = -1;
	for (int i = 1; i <= n; ++i) {
		if (d[i] > 0) {
			if (r == -1) r = f (i);
			else if (f (i) != r) sum = 1;
		}
	}
	if (sum) {
		cout << "non-Eulerian";
		return 0;
	}
	int o = 0;
	for (int i = 1; i <= n; ++i)
		if (d[i] % 2 == 1) o++;

	if (o == 0) cout << "Eulerian";
	else if (o == 2) cout << "Semi-Eulerian";
	else cout << "non-Eulerian";
	return 0;
}