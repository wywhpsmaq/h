#include<bits/stdc++.h>
using namespace std;
int main(){
	int x,y,k;
	cin>>x>>y>>k;
	vector<int> v;
	for(int i=2;i<1000;i++)
	{
		if(i%x!=0&&i%y!=0&&i%(10*x+y)!=0)
		{
			v.push_back(i);
		}
	}
	if(v.size()==0||k>v.size()) cout<<-1;
	cout<<v[v.size()-1];
	return 0;
}

