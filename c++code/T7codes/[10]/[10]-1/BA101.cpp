#include <bits/stdc++.h>
using namespace std;
int main()
{
    unsigned long long b, p;
    unsigned int k;
    cin >> b >> p >> k;
    cout << b << '^' << p << " mod " << k << '=';
    unsigned long long ans = 1 % k;
    b %= k;
    while (p > 0)
    {
        if (p & 1)
        {
            ans = (ans * b) % k;
        }
        b = (b * b) % k;
        p >>= 1;
    }
    cout << ans;
    return 0;
}