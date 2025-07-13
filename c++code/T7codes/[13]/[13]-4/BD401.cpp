#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int s = 0, f = 1; char ch = getchar_unlocked();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar_unlocked(); }
	while (isdigit(ch)) { s = (s << 3) + (s << 1) + ch - '0'; ch = getchar_unlocked(); }
	return s * f;
}
inline void write(long long x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	fflush(stdin);
	fflush(stdout);
	int n = read(), m = read();
	vector<vector<pair<int, int>>> p(n + 1);
	vector<int> d(n + 1, 0);
	for (int i = 0; i < m; ++i) {
		int u = read(), v = read(), w = read();
		p[u].push_back({v, w});
		d[v]++;
	}
	queue<int> q;
	vector<int> v;
	for (int i = 1; i <= n; ++i) if (d[i] == 0) q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		v.push_back(u);
		for (auto& e : p[u]) {
			int v = e.first;
			d[v]--;
			if (d[v] == 0) q.push(v);
		}
	}
	vector<int> ans(n + 1, -0x3f3f3f3f);
	ans[1] = 0;
	for (int u : v) {
		for (auto e : p[u]) {
			if (ans[u] + e.second > ans[e.first]) ans[e.first] = ans[u] + e.second;
		}
	}
	write((long long)ans[n]);
	return 0;
}