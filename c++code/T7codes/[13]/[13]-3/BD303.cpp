#include<bits/stdc++.h>
using namespace std;
int ans=1e9;
int p[510][510],d[510][510];
int main(){
	memset(p,0x3f3f3f3f,sizeof p);
	memset(d,0x3f3f3f3f,sizeof d);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		p[x][y]=p[y][x]=min(min(p[x][y],p[y][x]),z);
		d[x][y]=d[y][x]=p[x][y];
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<n;i++){
			for(int j=1;j<=n;j++){
				if(p[i][j]==0x3f3f3f3f||d[i][k]==0x3f3f3f3f||d[k][j]==0x3f3f3f3f){
					continue;
				}
				ans=min(ans,p[i][j]+d[i][k]+d[k][j]);
				bool f=0;
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(i==j||i==k||k==j) continue;
				p[i][j]=min(p[i][j],p[i][k]+p[k][j]);
			}
		}
	}
    if(ans==1e9) cout<<"No solution.";
	else cout<<ans;
	return 0;
}