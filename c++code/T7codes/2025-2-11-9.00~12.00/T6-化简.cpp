#include<bits/stdc++.h>
using namespace std;
bool z(int a,int b) {
	int c=max(a,b);
	for(int i=2; i<=c; i++) if(a%i==0&&b%i==0) return 0;
	return 1;
}
int main() {
	int a,b,c;
	cin>>a>>b>>c;
	int n=0,m=0;
	int d=99999;
	bool nn=0;
	if(b>a) {
		swap(a,b);
		nn=1;
	}
	for(int i=1; i<=c; i++) {
		for(int j=i; j<=c; j++) {
			if(z(i,j)) {
				if(j*b>=i*a) {
					if((j*b)-(i*a)<d) {
						n=i,m=j;
						d=(j*b)-(i*a);
					}
				}
			}
		}
	}
	if(!nn) cout<<m<<" "<<n;
	else cout<<n<<" "<<m;
	return 0;
}

