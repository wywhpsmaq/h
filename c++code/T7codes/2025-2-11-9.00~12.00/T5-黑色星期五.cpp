#include<bits/stdc++.h>
using namespace std;
int main() {
	int p[10]= {};
	int a,b;
	cin>>a;
	int num=6;
	for(int i=1900; i<=1900+a-1; i++) {
		for(int j=1; j<=12; j++) {
			p[num]++;
			if(j==2) {
				if(i%100==0) {
					if(i%400==0) {
						num+=1;
					}
				} 
                else if(i%4==0) num+=1;
                else num+=0;
			} else if(j==4||j==6||j==9||j==11) {
				num+=2;
			} else {
				num+=3;
			}
			num%=7;
		}
	}
	cout<<p[6]<<" "<<p[0]<<" ";
    for(int i=1;i<=5;i++) cout<<p[i]<<' ';
	return 0;
}

