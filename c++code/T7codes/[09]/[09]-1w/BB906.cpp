#include<bits/stdc++.h>
using namespace std;
int n, m, i, j;
vector<int> a(500);
vector<int> b(500);
vector<int> c(500);
int main()
{
	cin >> m >> n;
	a[0] = 1;
	a[1] = 1;
	b[0] = 1;
	b[1] = 0;
	for (j = m + 1; j <= n; j++)
	{
		for (i = 0; i <= a[0]; i++){
			c[i] = a[i];
		}
		for (i = 1; i <= a[0]; i++)
		{
			a[i] += b[i];
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
		while (a[a[0] + 1] > 0)
			a[0]++;
        for(int i=0;i<500;i++)
        {
            b[i]=0;
        }
		for (i = 0; i <= c[0]; i++)
			b[i] = c[i];
	}
	for (i = a[0]; i >= 1; i--)
		cout << a[i];
	return 0;
}