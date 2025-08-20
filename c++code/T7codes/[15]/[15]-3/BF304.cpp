#include<bits/stdc++.h>
using namespace std;
int ans[1100][1100];
int w[1100],v[1100];
bool vv[1145];
int main() {
	int t,n;
	cin>>t>>n;
	ans[0][0]=0;
	for(int i=1; i<=n; i++) {
		cin>>w[i]>>v[i];
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=t; j++) {
			if(j<w[i]) {
				ans[i][j]=ans[i-1][j];
			} else if(ans[i][j]<ans[i-1][j-w[i]]+v[i]&&j>=w[i]) {
				vv[i]=1;
				ans[i][j]=ans[i-1][j-w[i]]+v[i];
			} else {
				vv[j-1]=0;
			}
		}
	}
	for(int i=1; i<=n; i++) {
		if(vv[i]) cout<<i<<" ";
	}
}
