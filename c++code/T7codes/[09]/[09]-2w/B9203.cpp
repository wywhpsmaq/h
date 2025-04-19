#include <bits/stdc++.h>
using namespace std;
const int fx[] = {0, -2, -1, 1, 2, 2, 1, -1, -2},fy[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
int bx, by, mx, my;
long long f[99][99];
bool s[99][99];
int main()
{
    cin>>bx>>by>>mx>>my;
    bx += 2,by += 2,mx += 2,my += 2;
    f[2][1] = 1;
    for (int i = 0; i <= 8; i++){
        s[mx + fx[i]][my + fy[i]] = 1;
    }
    for (int i = 2; i <= bx; i++)
    {
        for (int j = 2; j <= by; j++)
        {
            if (s[i][j]) continue;
            f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }
    cout<<f[bx][by];
    return 0;
}
