#include<bits/stdc++.h>
using namespace std;
int main()
{
    int p[1000010] = {},n;
    p[1] = 1, p[2] = 2, p[3] = 5;
    cin >> n;
    if (n <= 3){
        cout << p[n];
        return 0;
    }
    for (int i = 4; i <= n; i++){
        p[i] = (p[i - 1] * 2 % 10000 + p[i - 3] % 10000) % 10000;
    }
    cout << p[n];
    return 0;
}
