#include<bits/stdc++.h>
using namespace std;
int main()
{
    int ans=0,ans_=0;
    srand(chrono::steady_clock::now().time_since_epoch().count());
    for(int i=0;i<1000000;i++)
    {
        int x=rand()%2;
        if(x==0)
            ans++;
        else
            ans_++;
    }
    cout<<(ans>ans_?"Yes!":"No!")<<endl;
}