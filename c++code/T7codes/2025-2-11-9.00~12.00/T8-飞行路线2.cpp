#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,d,e,f=0,ans=INT_MAX,m;
	cin>>a>>b>>c;
	for(int i=0;i<c;i++)
	{
		cin>>d>>e;
		for(int j=0;j<e;j++)
		{
			cin>>m;
			if(m==a)
			{
				f=1;
			}
			if(m==b&&f)
			{
				ans=min(ans,d);
			}
		}
		f=0;
	}
	cout<<(ans==INT_MAX?-1:ans);
	return 0;
}
