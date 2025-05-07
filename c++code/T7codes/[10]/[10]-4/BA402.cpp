#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long h[1000010];
bool check(long long a)
{
	long long t=0;
	for(long long i=1;i<=n;i++)
	{
		if(a<h[i])
		{
			t+=h[i]-a;
		}
	}
	if(t>=m)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	cin>>n>>m;
	long long r=0,l=1;
	for(long long i=1;i<=n;i++)
	{
		cin>>h[i];
		r=max(r,h[i]);
	}
	while(l<=r)
	{
		long long a=(l+r)/2;
		if(check(a))
		{
			l=a+1;
		}
		else 
		{
			r=a-1;
		}
	}
	cout<<l-1;
	return 0;
}