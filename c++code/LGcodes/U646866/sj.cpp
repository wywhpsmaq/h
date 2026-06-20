#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    freopen("U646866-sj\\U646866-17.in", "w", stdout);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> ns((INT_MAX + 1), LLONG_MAX - 1), xs(20, 2000), ys(20, 2000), sj((INT_MIN / 20), (INT_MAX / 20));
    int n = ns(gen), x = xs(gen)/*1e3*/, y = ys(gen)/*1e3*/;
    cout << n << " " << x << " " << y << '\n';
    for (int i = 0;i < x;i++) {
        for (int j = 0;j < y;j++) {
            cout << sj(gen) << " ";
        }
        cout << '\n';
    }
}