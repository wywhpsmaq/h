#include<bits/stdc++.h>
using namespace std;
long long int s[20],b[20],f[20];
long long int n,j,c=1,y=0,ans=LLONG_MAX;
void ff(int x) {
    if ( x <= n ) {
        for ( int i = 1 ; i <= n ; i ++ ) {
            if ( f[i] == 0 ) {
                c *= s[i],y += b[i],f[i] = 1;
                ans = min (ans , abs (c - y));
                ff (x + 1);
                f[i] = 0,c /= s[i],y -= b[i];
            }
        }

    }
}
int main() {
    cin >> n;
    for ( int i = 1 ; i <= n ; i ++ ) {
        cin >> s[i] >> b[i];
    }
    ff (1);
    cout << ans;
}
