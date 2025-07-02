#include <bits/stdc++.h>
using namespace std;
vector<int> fa;
int f(int x)
{
    if (fa[x] != x)
        fa[x] = f(fa[x]);
    return fa[x];
}
void ff(int x, int y)
{
    int fx = f(x), fy = f(y);
    if (fx != fy)
        fa[fx] = fy;
}
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    fa.resize(n + 10);
    for (int i = 0; i <= n; ++i)
    {
        fa[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        ff(x, y);
    }
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        if (f(x) == f(y))
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}