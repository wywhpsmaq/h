#include<bits/stdc++.h>
using namespace std;
#define itn int
itn dp[1145][1145];
string ans;
int main()
{
    itn n,m;
	char s[1145],s1[1145];
	cin>>n>>m;
	scanf("%s %s",s+1,s1+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i]==s1[j]){
				dp[i][j]=dp[i-1][j-1]+1;
                ans+=s[i];
			}
			else {
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}
	cout<<dp[n][m]<<'\n';
    cout<<ans;
}
