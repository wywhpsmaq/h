#include<bits/stdc++.h>
using namespace std;
int sp,n;
string c[206];
void sc() {
    for ( int i = 1 ; i <= 2 * n + 2 ; i ++ ) {
        cout << c[i];
    }
    cout << endl;
}
void f(int p) {
    for ( int j = 0 ; j <= 1 ; j ++ ) {
        c[sp + j] = c[p + j];
        c[p + j] = "-";
    }
    sp = p;
    sc ();
}
void ff(int k) {
    if ( k == 4 ) {
        f (4),f (8),f (2),f (7),f (1);
    } else {
        f (k);
        f (2 * k - 1);
        ff (k - 1);
    }
}
int main() {
    cin>>n;
    for ( int i = 1 ; i <= n ; i ++ ) {
        c[i] = "o";
    }
    for ( int i = n + 1 ; i <= 2 * n ; i ++ ) {
        c[i] = "*" , c[2 * n + 1] = "-" , c[2 * n + 2] = "-";
    }
    sp = 2 * n + 1;
    sc ();
    ff (n);
}