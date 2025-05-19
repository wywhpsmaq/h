#include <bits/stdc++.h>
using namespace std;
int main() {
    int ans = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> f(1, 100);
    for (int i = 0; i < 6969; i++) {
        int n = f(gen);
        if (n % 2 == 0) {
            ans--;
        } else {
            ans++;
        }
    }
    if (ans > 0) {
        cout << "YES" << endl;
    } else if (ans == 0) {
        cout << "YESYESYYEESS" << endl;
    } else {
        cout << "NO" << endl;
    }
}