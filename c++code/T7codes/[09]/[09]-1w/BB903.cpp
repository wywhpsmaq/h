#include<bits/stdc++.h>
using namespace std;
int main()
{
	vector<int> a,b;
	int n,m;
	cin>>n;
	a.push_back(0);
	b.push_back(0);
	a.push_back(1);
	b.push_back(8);
	for(int i=2;i<=n;i++)
	{
		a.push_back((b[i-1]+9*a[i-1])%12345);
		b.push_back((a[i-1]+9*b[i-1])%12345);
	}
	cout<<b[n];
}