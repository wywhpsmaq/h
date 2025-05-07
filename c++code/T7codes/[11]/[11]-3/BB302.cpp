#include <bits/stdc++.h>
#pragma GCC optimize(2)
typedef long long ll;
using namespace std;
int n, p[99];
bool zs(int n) {
    if (n == 2) return 1;
    int ei = sqrt(n);
    for (int i = 2; i <= ei; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
bool f() {
    for (int i = 0; i < n; i++) {
        int ch = p[i];
        if (i == n - 1) {
            ch += p[0];
        } else {
            ch += p[i + 1];
        }
        if (!zs(ch)) {
            return 0;
        }
    }
    return 1;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
    }
    while (1) {
        if (f()) {
            for (int i = 0; i < n; i++) {
                cout << p[i] << " ";
            }
            cout << '\n';
        }
        if (!next_permutation(p, p + n)) break;
    }
}