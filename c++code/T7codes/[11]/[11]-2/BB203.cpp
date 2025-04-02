#include<bits/stdc++.h>
using namespace std;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
vector<vector<int>> p;
int a,b,ans=INT_MAX;
void dfs(int x,int y,int num){
    p[x][y]=1;
    if(x==a-1&&y==b-1)
    {
        ans=min(ans,num);
    }
    for(int i=0;i<4;i++){
       int nx=x+dx[i];
       int ny=y+dy[i];
       if(nx>=0&&nx<a&&ny>=0&&ny<b&&p[nx][ny]==0){
        dfs(nx,ny,num+1);
        p[nx][ny]=0;
       } 
    }
    return;
}
int main()
{
    cin>>a>>b;
    p.resize(a,vector<int>(b));
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            char c;
            cin>>c;
            if(c=='#') p[i][j]=1;
            else p[i][j]=0;
            cin>>p[i][j];
        }
    }
    dfs(0,0,1);
    cout<<ans;
}