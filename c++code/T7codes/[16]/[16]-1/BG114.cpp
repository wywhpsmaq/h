#include <bits/stdc++.h>
using namespace std;
struct node {
	int x, y, v;
} p[114514];
int dp[114514], ans;
int hfm (int x, int y, int xx, int yy) {
	return abs (x - xx) + abs (y - yy);
}
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> p[i].v >> p[i].x >> p[i].y;
	for (int i = 1; i <= m; i++) {
		dp[i] = 1;
		for (int j = 1; j < i; j++) {
			if (hfm (p[i].x, p[i].y, p[j].x, p[j].y) <= p[i].v - p[i].v) { dp[i] = max (dp[i], dp[j] + 1); }
		}
	}
	for (int i = 1; i <= m; i++) { ans = max (ans, dp[i]); }
	cout << ans;
}
/*
#include <bits/stdc++.h>
using namespace std;
struct uu {
	int x, y, v;
} p[114514];
int dp[114514];
int hfm (int x, int y, int xx, int yy) {
	return abs (x - xx) + abs (y - yy);
}
int main () {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> p[i].v >> p[i].x >> p[i].y;
	for (int i = 1; i <= m; i++) {
		dp[i] = 1;
		for (int j = 1; j < i; j++) {
			if (hfm (p[i].x, p[i].y, p[j].x, p[j].y) <= p[i].v - p[j].v) { dp[i] = max (dp[i], dp[j] + 1); }
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) ans = max (ans, dp[i]);
	cout << ans;
}
*/