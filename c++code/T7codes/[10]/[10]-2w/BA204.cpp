#include<bits/stdc++.h>
using namespace std;
int main() {
    int n , a[999999] , b[999999] , ans = INT_MIN;
    cin >> n;
    for ( int i = 1 ; i <= n ; i ++ ) {
        cin >> a[i];
        if ( i == 1 ) b[i] = a[i];
        else b[i] = max (a[i] , b[i - 1] + a[i]);
        ans = max (ans , b[i]);
    }
    cout << ans;
}