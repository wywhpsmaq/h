#include<bits/stdc++.h>
using namespace std;
char c[999][999];
void f(int n, int a, int b) {
    if (n == 1) {
        c[a][b] = '/', c[a][b + 1] = '\\', c[a - 1][b - 1] = '/', c[a - 1][b] = '_', c[a - 1][b + 1] = '_', c[a - 1][b + 2] = '\\';
        return;
    }
    f(n - 1, a / 2 + 1, b);
    int x = a - (a - 1), y = b - (a / 2 + 1), x1 = a, y1 = b - (2 * a - 1), x2 = a, y2 = b + 1, n1 = (a - 1) * 2;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            c[x1 + i][y1 + j] = c[x + i][y + j];
            c[x2 + i][y2 + j] = c[x + i][y + j];
        }
    }
    return;
}
int main() {
    int a;
    cin >> a;
    int b = pow(2, a);
    f(a, b / 2 + 1, b);
    for (int i = 1; i <= b; i++) {
        for (int j = 1; j <= b * 2; j++) {
            if (c[i][j] != '/' && c[i][j] != '_' && c[i][j] != '\\') {
                cout << " ";
            } else {
                cout << c[i][j];
            }
        }
        cout << '\n';
    }
}