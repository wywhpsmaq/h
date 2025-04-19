#include <bits/stdc++.h>
using namespace std;
int p[999][999], a, b, n, x, y;
bool f[999][999];
int main()
{
    memset(f,true,sizeof(f));
    cin >> a >> b >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x >> y;
        f[x][y] = 0;
    }
    for (int i = 1; i <= a; i++)
    {
        if (!f[i][1])
        {
            break;
        }
        p[i][1] = 1;
    }
    for (int i = 1; i <= b; i++)
    {
        if (!f[1][i])
        {
            break;
        }
        p[1][i] = 1;
    }
    for (int i = 2; i <= a; i++)
    {
        for (int j = 2; j <= b; j++)
        {
            if (f[i][j])
            {
                p[i][j] = p[i - 1][j] + p[i][j - 1];
            }
        }
    }
    cout << p[a][b];
    return 0;
}