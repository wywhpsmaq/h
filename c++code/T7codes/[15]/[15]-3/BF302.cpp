#include<bits/stdc++.h>
using namespace std;
long long dp[1145];
int main() {
	int n,m;
	cin>>n>>m;
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	vector<pair<int,int>> v;
	v.push_back(make_pair(0,0));
	for(int i=0; i<m; i++) {
		int x,y;
		cin>>x>>y;
		v.push_back(make_pair(x,y));
	}
	for(int i=1; i<=m; i++) {
		for(int j=n; j>=1; j--) {
			for(int k=1; k<=j; k++) {
				auto [a,b]=v[i];
				long long num=1ll*a*pow(k,b);
				dp[j]=min(dp[j],dp[j-k]+num);
			}
		}
	}
	cout<<dp[n];
}
