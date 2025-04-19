#include<bits/stdc++.h>
using namespace std;
int main() {
	vector<int> v;
	int n,k;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	for(int i=3;i<50;i++)
	{
		v.push_back((v[i-1]+v[i-2]));
	}
	cin>>k;
	cout<<v[k]<<'\n';
	return 0;
}