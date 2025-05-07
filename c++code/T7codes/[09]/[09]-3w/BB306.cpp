#include <bits/stdc++.h>
using namespace std;
int f(int m, int n) {
    if ( m == 0 ) return 1;
    if ( n == 0 ) return 0;
    if ( m < 0 ) return 0;
    return f (m , n - 1) + f (m - n , n);
}
int main() {
    int t;
    cin >> t;
    while ( t -- ) {
        int m , n;
        cin >> m >> n;
        cout << f (m , n) << endl;
    }
    return 0;
}