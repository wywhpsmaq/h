#include<bits/stdc++.h>
using namespace std;
int n, m, x, y, a[100010];
string s;
int main()
{
    cin >> n >> m;
    for (int i = 1;i <= n;i++) cin >> a[i];
    while (m--)
    {
        cin >> x >> y >> s;
        if (s == "Completed") a[x] = y;
    }
    for (int i = 1;i <= n;i++) cout << a[i] << " ";
}