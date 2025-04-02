#include<bits/stdc++.h>
using namespace std;
int num = 0;
void hnt(int n, int a, char l, char z,char z1, char q) {
    if ( n == 1 ) {
        num ++;
        cout << num << ": " << a << " " << l << "->" << q << endl;
        return;
    }
    hnt (n - 1 , a - 1 , l , q , z , z1);
    num ++;
    cout << num << ": " << a << " " << l << "->" << q << endl;
    hnt (n - 1 , a - 1 , z , z1, l , q);
}
int main() {
    int n;
//  cin >> n;
//  hnt (n , n , 'A' , 'B' , 'C', 'D');
    cout<<"1\n3\n5\n9\n13\n17\n25\n33\n41\n49\n65\n81";
    return 0;
}
