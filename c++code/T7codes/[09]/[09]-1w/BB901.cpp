#include<bits/stdc++.h>
using namespace std;
int main() {
	vector<int> v;
	int n,k;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	for(int i=3;i<350005;i++)
	{
		v.push_back((2*v[i-1]+v[i-2])%10007);
	}
	cin>>n;
	while(n)
	{
		cin>>k;
		cout<<v[k]<<'\n';
		n--;
	}
	return 0;
}