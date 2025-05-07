#include<bits/stdc++.h>
using namespace std;
int num = 0;
void hnt(int n, int a, char l, char z, char q) {
    if ( n == 1 ) {
        num ++;
        cout << num << ": " << a << " " << l << "->" << q << endl;
        return;
    }
    hnt (n - 1 , a - 1 , l , q , z);
    num ++;
    cout << num << ": " << a << " " << l << "->" << q << endl;
    hnt (n - 1 , a - 1 , z , l , q);
}
int main() {
    int n;
    cin >> n;
    hnt (n , n , 'A' , 'B' , 'C');
    return 0;
}
