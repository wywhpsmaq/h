#include <bits/stdc++.h>
using namespace std;
int a[5000], b[5000], c[5000];
int main()
{
    int n;
    int x = 1;
    cin >> n;
    if (n < 3)
    {
        cout << n;
        return 0;
    }
    a[1] = 1;
    b[1] = 2;
    for (int i = 3; i <= n; i++)
    {
        for (int j = 1; j <= x; j++)
            c[j] = a[j] + b[j];
        for (int j = 1; j <= x; j++)
        {
            if (c[j] > 9)
            {
                c[j + 1] = c[j + 1] + c[j] / 10;
                c[j] %= 10;
                if (j + 1 > x)
                    x++;
            }
        }
        for (int j = 1; j <= x; j++)
            a[j] = b[j];
        for (int j = 1; j <= x; j++)
            b[j] = c[j];
    }
    for (int i = x; i > 0; i--)
        cout << b[i];
    return 0;
}