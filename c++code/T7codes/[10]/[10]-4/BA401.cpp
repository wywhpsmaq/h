#include <bits/stdc++.h>
using namespace std;
int n,k;
int a[100007];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++){
        cin>>a[i];
    }
	int l=0,r=1e8+1,m;
	while(l+1<r)
	{
		m=(l+r)/2;
		int cnt=0;
		for(int i=1;i<=n;i++)
		cnt+=a[i]/m;
		if(cnt>=k){
            l=m;
        }
		else r=m;
	}
	cout<<l;
	return 0;
}