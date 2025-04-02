#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> dp;
int xm(int num, int bh)
{
    if (dp[num][bh] != 0) return dp[num][bh];
    if (num == m && bh == 1) return 1;
    int l = (bh == 1) ? n : bh - 1;
    int r = (bh == n) ? 1 : bh + 1;
    int o = 0;
    if (num < m)
    {
        o = xm(num + 1, l) + xm(num + 1, r);
    }
    dp[num][bh] = o;
    return dp[num][bh];
}

int main()
{
    cin >> n >> m;
    dp.resize(m + 1, vector<int>(n + 1, 0));
    cout << xm(0, 1) << endl;
    return 0;
}
