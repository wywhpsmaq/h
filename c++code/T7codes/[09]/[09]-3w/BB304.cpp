#include <bits/stdc++.h>
using namespace std;
long long f(int a)
{
    long long ans = 1;
    for (int i = 2; i <= a; ++i)
    {
        ans *= i;
    }
    return ans;
}
int main()
{
    int n, k;
    cin >> n >> k;
    cout << f(n) / (f(k) * f(n - k));
}