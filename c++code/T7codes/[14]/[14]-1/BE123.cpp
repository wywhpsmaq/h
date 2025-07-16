#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, x, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x == 0 && ans % 2 != 0) ans++;
        if (x == 1 && ans % 2 == 0) ans++;
    }
    cout << ans + 1;
}