#include<bits/stdc++.h>
using namespace std;
long long a,b,c,p[99][99][99];
long long w(long long i,long long j,long long k) {
    if ( i <= 0 || j <= 0 || k <= 0 ) return 1;
    if ( i > 20 || j > 20 || k > 20 ) return w (20 , 20 , 20);
    if ( i < j && j < k ) {
        if ( p[i][j][k - 1] == 0 ) {
            p[i][j][k - 1] = w (i , j , k - 1);
        }
        if ( p[i][j - 1][k - 1] == 0 ) {
            p[i][j - 1][k - 1] = w (i , j - 1 , k - 1);
        }
        if ( p[i][j - 1][k] == 0 ) {
            p[i][j - 1][k] = w (i , j - 1 , k);
        }
        p[i][j][k] = p[i][j][k - 1] + p[i][j - 1][k - 1] - p[i][j - 1][k];
    } else {
        if ( p[i - 1][j][k] == 0 ) {
            p[i - 1][j][k] = w (i - 1 , j , k);
        }
        if ( p[i - 1][j - 1][k] == 0 ) {
            p[i - 1][j - 1][k] = w (i - 1 , j - 1 , k);
        }
        if ( p[i - 1][j][k - 1] == 0 ) {
            p[i - 1][j][k - 1] = w (i - 1 , j , k - 1);
        }
        if ( p[i - 1][j - 1][k - 1] == 0 ) {
            p[i - 1][j - 1][k - 1] = w (i - 1 , j - 1 , k - 1);
        }
        p[i][j][k] = p[i - 1][j][k] + p[i - 1][j - 1][k] + p[i - 1][j][k - 1] - p[i - 1][j - 1][k - 1];
    }
    return p[i][j][k];
}
int main() {
    while ( 1 ) {
        cin >> a >> b >> c;
        if ( a == - 1 && b == - 1 && c == - 1 ) return 0;
        cout << "w(" << a << ", " << b << ", " << c << ')' << " = " << w (a , b , c) <<'\n';
    }
}
