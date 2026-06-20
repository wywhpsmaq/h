#include<bits/stdc++.h>
using namespace std;
char c[105][105];
int main() {
    freopen("U514492-1.in", "w", stdout);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> n(1, 100), m(1, 100), dt(1, 100), ddt(0, 9), xl(1, 50);
    int n1 = n(gen), m1 = m(gen);
    for (int i = 0;i < n1;i++) {
        for (int j = 0;j < m1;j++) {
            int o = dt(gen);
            if (o <= 50) c[i][j] = '.';
            else if (o <= 60) c[i][j] = '*';
            else if (o <= 70) c[i][j] = '&';
            else if (o <= 85) c[i][j] = ddt(gen) + '0';
            else c[i][j] = '|';
        }
    }
    uniform_int_distribution<> p(0, n1 - 1), q(0, m1 - 1);
    c[p(gen)][q(gen)] = '@';
    c[p(gen)][q(gen)] = '~';

    cout << n1 << " " << m1 << " " << xl(gen) << endl;
    for (int i = 0;i < n1;i++) {
        for (int j = 0;j < m1;j++) {
            cout << c[i][j];
        }
        cout << endl;
    }
}