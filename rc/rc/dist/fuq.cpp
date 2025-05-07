#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> f(1, 100);
    freopen("fuq.txt", "w", stdout);
    int n = f(gen);
    if (n < 65) {
        cout << 0;
    } else if (n < 85) {
        cout << 1;
    } else {
        cout << 2;
    }
}
