#include<bits/stdc++.h>
using namespace std;
long long f(int a)
{
	if(a==0)
	{
		return 0;
	}
	long long ans=1;
	for(int i=1;i<=a/2;i++)
	{
		ans+=f(i);
	}
	return ans;
}
int main()
{
	int a;
	cin>>a;
	cout<<f(a);
}