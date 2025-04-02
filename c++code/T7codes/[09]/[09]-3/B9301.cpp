#include<bits/stdc++.h>
using namespace std;
long long f(int a)
{
    if(a==0)
    {
        return 0;
    }
    return a+f(a-1);
}
int main() {
	int a;
    cin>>a;
    cout<<f(a);
    return 0;
}
