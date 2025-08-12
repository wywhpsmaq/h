#include <bits/stdc++.h>
using namespace std;
long long b[50][50];
void v () {
	for (int i = 0; i < 50; i++) {
		b[i][0] = 1;
		if (i > 0) b[i][i] = 1;
		for (int j = 1; j < i; j++) { b[i][j] = b[i - 1][j - 1] + b[i - 1][j]; }
	}
}
long long dfs (int i, int l, int r, string s, vector<vector<vector<long long>>> &p) {
	int l = s.size ();
	if (i == l) return 1;
	if (p[i][l][r] != -1) return p[i][l][r];
	long long res = 0;
	int lb, ub;
	if (i == 0) lb = 1;
	else lb = l;
	if (r) ub = s[i] - '0';
	else ub = 9;
	if (lb > ub) res = 0;
	else {
		for (int d = lb; d <= ub; d++) {
			int new_r = r && (d == ub);
			int new_l = d;
			res += dfs (i + 1, new_l, new_r, s, p);
		}
	}
	p[i][l][r] = res;
	return res;
}
long long f (string s) {
	int l = s.size ();
	vector<vector<vector<long long>>> p (l + 1, vector<vector<long long>> (10, vector<long long> (2, -1)));
	return dfs (0, 0, 1, s, p);
}
long long dfs1 (int i, int l, int r, string s, vector<vector<vector<long long>>> &p) {
	int len = s.size ();
	if (i == len) return 1;
	if (p[i][l][r] != -1) return p[i][l][r];
	long long res = 0;
	int lb, ub;
	if (l == 10) lb = 1;
	else lb = 0;
	if (r) ub = s[i] - '0';
	else ub = 9;
	if (l != 10) { ub = min (ub, l); }
	if (lb > ub) res = 0;
	else {
		for (int d = lb; d <= ub; d++) {
			int new_r = r && (d == ub);
			int new_l = d;
			res += dfs1 (i + 1, new_l, new_r, s, p);
		}


	}
	p[i][l][r] = res;
	return res;
}
long long len (const string &s) {
	int l = s.size ();
	vector<vector<vector<long long>>> p (l + 1, vector<vector<long long>> (11, vector<long long> (2, -1)));
	return dfs1 (0, 10, 1, s, p);
}
int main () {
	ios_base::sync_with_stdio (false);
	cin.tie (0);
	v ();
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int l = s.size ();
		long long aum = 0;
		if (l > 1) { aum += 9l * (l - 1); }
		for (int c = 1; c <= 9; c++) {
			string ss (l, '0' + c);
			if (ss <= s) { aum++; }
		}
		long long sum = 0;
		for (int k = 1; k < l; k++) { sum += b[k + 8][8]; }
		sum += f (s);
		long long num = 0;
		for (int k = 1; k < l; k++) {
			int m = k - 1;
			long long sum_val = 0;
			for (int d1 = 1; d1 <= 9; d1++) { sum_val += b[m + d1][m]; }
			num += sum_val;
		}
		num += len (s);
		long long ans = sum + num - aum;
		cout << ans;
	}
	return 0;
}