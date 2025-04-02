#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	double q[99999],p[99999],ans=0.00;
	q[1]=2,p[1]=1;
	for(int i=2;i<=m;i++)
	{
		q[i]=p[i-1]+q[i-1];
		p[i]=q[i-1];
		if(i>=n) ans+=q[i]/p[i];
	}
	printf("%.3f",ans);
	return 0;
}

