#include<bits/stdc++.h>
using namespace std;
int n,m;
int dp[114][114][114];
char c[1145][1145];
int main()
{
    cin>>n>>m;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            cin>>c[i][j];
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<(1<<m)-1;j++)
        {
            if (j&j<<1) continue;
            if (j&j<<2) continue;
            if (j&j>>1) continue;
            if (j&j>>2) continue;
            for (int k=0;k<(1<<m)-1;k++)
            {
                int num=0,sum=j;
                while (sum)
                {
                    if (sum&1) num++;
                    sum>>=1;
                }
                dp[i][j][k]=max(dp[i][j][k],dp[i-1][j][k]+num);
            }
        }
    }
}