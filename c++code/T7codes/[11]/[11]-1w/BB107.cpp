#include <bits/stdc++.h>
using namespace std;
int ans;
int p[999][999];
int k[3]={0,+1,-1};
int o[3]={-1,1,0};
int dfs(int x,int y)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            p[x][y] = 0;
            if(p[x + k[i]][y + o[j]]!=0) dfs(x + k[i], y + o[j]);
        }

    }
    return 0;

}
int main()
{
    int n,m;
    cin>>n>>m;
    char c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin>>c;
            if(c=='W') p[i][j]=1;
            else p[i][j]=0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if(p[i][j]==1) dfs(i,j),ans++;
        }
    }
    cout<<ans;
}