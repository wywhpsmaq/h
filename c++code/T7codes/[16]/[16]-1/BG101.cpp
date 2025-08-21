#include <bits/stdc++.h>
using namespace std;
int dp[1145],n,v[1145];
int main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	cin>>n;
	for(int i=1;i<=n;i++){
		dp[i]=1;
		cin>>v[i];
		for(int j=1;j<=i;j++)
		{
			if(v[j]<v[i]){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i]);
	}
	cout<<ans;
}
