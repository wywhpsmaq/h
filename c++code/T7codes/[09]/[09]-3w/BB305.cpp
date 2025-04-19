#include<bits/stdc++.h>
using namespace std;
int f(int a, int s) {
    if ( a == 1 ) {
        return 1;
    }
    int ans = 0;
    for ( int i = s ; i * i <= a ; ++ i ) {
        if ( a % i == 0 ) {
            ans += f (a / i , i);
        }
    }
    ans += 1;
    return ans;
}
int main() {
    int n , a;
    cin >> n;
    for ( int i = 0 ; i < n ; ++ i ) {
        cin >> a;
        cout << f (a , 2) << endl;
    }
    return 0;
}