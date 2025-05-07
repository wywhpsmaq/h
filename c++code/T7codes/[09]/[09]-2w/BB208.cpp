#include <bits/stdc++.h>
using namespace std;
int main() {
    int h , k , ans = 0;
    cin >> h >> k;
    ans = k + 1;
    for ( int i = 1 ; i <= h ; i ++ ) {
        ans = ans * 2;
    }
    cout << ans;
}