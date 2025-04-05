//
// Created by Administrator on 2024/12/22.
//
#include <bits/stdc++.h>
using namespace std;
int n,an=0,ans=-1;
string tr[30];
int yc[30][30],v[30];
int mt(int x, int y) {
    bool pp = true;
    int ky = 0;
    for ( int k = tr[x] . size () - 1 ; k >= 0 ; k -- ) {
        for ( int kx = k ; kx < tr[x] . size () ; kx ++ ) {
            if ( tr[x][kx] != tr[y][ky ++] ) {
                pp = false;
                break;
            }
        }
        if ( pp == true ) return tr[x] . size () - k;
        ky = 0 , pp = true;
    }
    return 0;
}
char ch;
int dfs(int p) {
    bool jx = false;
    for ( int j = 1 ; j <= n ; j ++ ) {
        if ( v[j] >= 2 ) continue;
        if ( yc[p][j] == 0 ) continue;
        if ( yc[p][j] == tr[p] . size () || yc[p][j] == tr[j] . size ()) continue;
        an += tr[j] . size () - yc[p][j] , v[j] ++ , jx = true;
        dfs (j);
        an -= tr[j] . size () - yc[p][j] , v[j] --;
    }
    if ( jx == false ) ans = max (ans , an);
    return 0;
}
int main() {
    cin >> n;
    for ( int i = 1 ; i <= n ; i ++ ) cin >> tr[i];
    cin >> ch;
    for ( int i = 1 ; i <= n ; i ++ ) {
        for ( int j = 1 ; j <= n ; j ++ ) {
            yc[i][j] = mt (i , j);
        }
    }
    for ( int i = 1 ; i <= n ; i ++ ) {
        if ( tr[i][0] == ch ) {
            v[i] ++;
            an = tr[i] . size ();
            dfs (i);
            v[i] = 0;
        }
    }
    cout << ans << '\n';
}