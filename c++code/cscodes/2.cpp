#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
int n,m;
int sd=1000,num=0;
vector<vector<int>>cc;
void sc(){
    random_device r;
    mt19937 ge(r());
    uniform_int_distribution<> f(1,29);
    int x=f(ge),y=f(ge);
    while(cc[x][y]==1||(x==15&&y==15)){x=f(ge),y=f(ge);}
    cc[x][y]=1;
}
pair<int,int> sr()
{
    int nx,ny;
    int nn=time(0);
    char c=getchar_unlocked();
    if(c=='8') {nx=1,ny=0;}
    else if(c=='4') {nx=0,ny=-1;}
    else if(c=='2') {nx=-1,ny=0;}
    else if(c=='6') {nx=0,ny=1;}
    return make_pair(nx,ny);
}
void yd(pair<int,int> s,pair<int,int> e){
    if(cc[e.first][e.second]==1){num++;}
    
}
int main()
{
    random_device rd;
	mt19937 gen (rd ());
	uniform_int_distribution<> f (0,1);
    n=29,m=29;
    for(int i=0;i<10;i++)
    {
        sc();
    }
    int x=15,y=15;
    cc[x][y]=11;
    while(num<(29*29)/2){
        sd=1000-num;
        this_thread::sleep_for(chrono::milliseconds(sd));
        int nx,ny;
        pair<int,int> next=sr();
        if(next.first!=10&&next.second!=10){
            nx=x+next.first,ny=y+next.second;
        }
        yd({x,y},{nx,ny});
    }
}