#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b;
    cin>>a>>b;
    int num=b*2;
    for(int i=b+1;i<=a;i++) num+=i;
    cout<<num;
    return 0;
}
