#include <bits/stdc++.h>
using namespace std;
int n,s[11451],f[1145],max1=INT_MIN,ss[1145],sf[1145],sm[1145];
void dfs(int x,int sum,int num) {
	if(x==n+1) {
		if(sum+num>max1&&sum>=0&&num>=0) max1=sum+num;
		return;
	}
	if(sum+ss[x]<=0||num+sf[x]<=0||sum+num+sm[x]<=max1) {
		return;
	}
	dfs(x+1,sum+s[x],num+f[x]);
	dfs(x+1,sum,num);
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>s[i]>>f[i];
	}
	for(int i=n; i>=1; i--) {
		ss[i]=ss[i+1]+max(0,s[i]);
		sf[i]=sf[i+1]+max(0,f[i]);
		sm[i]=sm[i+1]+max(0,s[i]+f[i]);
	}
	dfs(1,0,0);
	if(max1<=0) cout<<0;
	else cout<<max1;
}
