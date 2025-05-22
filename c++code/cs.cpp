#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> t[10086];
int main()
{
    cin>>n;
    for(int i=0;i<n-1;++i)
    {
        int x,y;
        cin>>x>>y;
        t[x].push_back(y);
        t[y].push_back(x);
    }
}