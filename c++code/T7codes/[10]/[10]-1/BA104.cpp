#include<bits/stdc++.h>
using namespace std;
int mp(long long p) {
    long long ans = 1 , b = 2011 , m = 10000;
    while ( p ) {
        if ( p & 1 ) ans = (ans * b) % m;
        b = (b * b) % m;
        p >>= 1;
    }
    return (int) ans;
}
int main(){
    int k;
    cin >> k;
    while(k--){
        long long n;
        cin >> n;
        cout << mp(n) << '\n';
    }
    return 0;
}