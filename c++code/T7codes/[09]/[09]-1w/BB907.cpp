#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,c,p[9999];
	cin>>a>>b>>c;
	for(int i=0;i<=a;i++){
		p[i]=1;
	}
	for(int i=a+1;i<=2*a+2;i++){
		p[i]=p[i-1]+b;
	}
	for(int i=2*a+3;i<=c;i++){
		p[i]=p[i-1]+(b*p[i-(a+2)]);
	}
	cout<<p[c-1];
}