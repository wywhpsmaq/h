#include<bits/stdc++.h>
using namespace std;
int fff(int a)
{
	if(a==1)
	{
		return 1;
	}
	else if(a==2)
	{
		return 2;
	}
	return fff(a-1)+fff(a-2);
}
int main()
{
	int a,n;
	cin>>a;
	n=fff(a);
	cout<<n;
}