#include <bits/stdc++.h>
using namespace std;
int main() {
    long long a , n , m , x;
    cin >> a >> n >> m >> x;
    int o = 1;
    if ( n - 2 > o ) o = n - 2;
    if ( x - 1 > o ) o = x - 1;
    vector < long long > f (o + 2 , 0);
    f[1] = 1 , f[2] = 1;
    for ( int i = 3 ; i <= o ; i ++ ) f[i] = f[i - 1] + f[i - 2];
    long long d = f[n - 2] - 1 , b = 0 , num = m - a * (f[n - 3] + 1) , ans = 0;
    if ( num % d != 0 ) {
        cout << "No answer.";
        return 0;
    }
    b = num / d;
    if ( x == 1 || x == 2 ) {
        ans = a;
    } else if ( x >= 3 && x <= n - 1 ) {
        ans = a * (f[x - 2] + 1) + b * (f[x - 1] - 1);
    } else if ( x == n ) {
        ans = 0;
    } else {
        cout << "No answer.";
        return 0;
    }
    cout << ans;
    return 0;
}