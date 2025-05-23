#include <iostream>
    using namespace std;
int a[10][10];
int main() {
    int m = 5, n = 4;
    for (int x = 0; x <= m; x++)
        a[x][0] = 1;
    for (int y = 1; y <= n; y++)
        a[0][y] = 1;
    for (int x = 1; x <= m; x++)
        for (int y = 1; y <= n; y++)
            a[x][y] = a[x - 1][y] + a[x][y - 1];
    cout << a[m][n] << endl;
    return 0;
