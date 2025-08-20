#include<bits/stdc++.h>
using namespace std;
int dp[114514];
struct uu {
	int a,b,c;
	uu(int x,int y,int z):a(x),b(y),c(z) {}
	bool operator < (uu d){
		return c*d.b<d.c*b;
	}
};
int main() {
	int t,n,x;
	cin>>t>>n;
	vector<uu> v;
	v.push_back(uu(0,0,0));
	for(int i=0; i<n; i++) {
		cin>>x;
		v.push_back(uu(x,0,0));
	}
	for(int i=1; i<=n; i++) {cin>>x;v[i].b=x;}
	for(int i=1; i<=n; i++) {cin>>x;v[i].c=x;}
	sort(v.begin()+1,v.end());
	for(int i=1;i<=n;i++) {
		for(int j=t;j>=v[i].c;j--) {
			dp[j]=max(dp[j],dp[j-v[i].c]+v[i].a-j*v[i].b);
		}
	}
	int ans=0;
	for(int i=0;i<t;i++) {
		ans=max(ans,dp[i]);
	}
	cout<<ans;
}
