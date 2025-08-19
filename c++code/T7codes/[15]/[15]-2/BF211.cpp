#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,V;
int a[1100][1100],b[1100][1100],s[1100],dp[11000];
signed main() {
	cin >> V >> n;
	for(int i = 1; i <= n; i++) {
		int x,y,z;
		cin >> x >> y >> z;
		s[z]++;
		a[z][s[z]] = x;
		b[z][s[z]] = y;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = V; j >= 0; j--) {
			for(int k = 1; k <= s[i]; k++) {
				if(j >= a[i][k]) {
					dp[j] = max(dp[j],dp[j - a[i][k]] + b[i][k]);
				}
			}
		}
	}
	cout << dp[V];
	return 0;
}