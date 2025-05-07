#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b;
	vector<int> p(9999);
	cin>>a;
	p[1]=1;
	p[2]=1;
	for(int i=3;i<=a;i++)
	{
		p[i]=p[i-1]+p[i-2];
	}
	cout<<p[a];
	return 0;
}