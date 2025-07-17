#include<bits/stdc++.h>
using namespace std;
int main()
{
    random_device rd;
    mt19937 gen (rd ());
    uniform_int_distribution < > dis(0,1);
    int ans=0;
    for(long long i=0;i<1000000000;i++)
    {
        if(dis(gen))
        {
            ans++;
        }
        else
        {
            ans--;
        }
    }
    cout<<(ans>0?"YES!!!!":"NO!!!\nNo!!!\nnO!!!\nno!!!");
}