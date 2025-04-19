#include<bits/stdc++.h>
using namespace std;
long long p[999][999],n, k;
int f(int x,int y) {
	if(x>n) return 0;
	else p[x][y]=p[x-1][y-1] + y * p[x-1][y];
	if(y<=x) f(x,y+1);
	else f(x+1,1);
	return 0;
}
int main() {
	cin >> n >> k;
	p[0][0] = 1;
	f(1,1);
	cout << p[n][k];
	return 0;
}