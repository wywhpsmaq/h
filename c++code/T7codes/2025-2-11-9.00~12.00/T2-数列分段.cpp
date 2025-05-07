#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,ans=0,num=0;
	int p[99999];
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>p[i];
		num+=p[i];
		if(num>m)
		{
			num=p[i];
			ans++;
		}
	}
	cout<<ans;
	return 0;
}

