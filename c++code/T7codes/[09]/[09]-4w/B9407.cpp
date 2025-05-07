#include<bits/stdc++.h>
using namespace std;
void hnt(int n, int a, char l, char z, char q) {
    if ( n == 1 ) {
        cout << a << " " << l << " " << q << endl;
        return;
    }
    hnt (n - 1 , a - 1 , l , q , z);
    cout << a << " " << l << " " << q << endl;
    hnt (n - 1 , a - 1 , z , l , q);
}
int main() {
    int n;
    cin >> n;
    hnt (n , n , 'A' , 'C' , 'B');
    return 0;
}
