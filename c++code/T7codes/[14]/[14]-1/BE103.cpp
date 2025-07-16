#include<bits/stdc++.h>
using namespace std;
int n, a[10005], num = 0, ans = 0;
bool f = 1;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        num += a[i];
    }
    num /= n;
    for (int i = 1; i <= n; i++) {
        a[i] -= num;
        if (a[i] != 0) f = 0;
    }
    if (f == 0) {
        for (int i = 1; i <= n; i++) {
            if (a[i] != 0) {
                if (a[i] > 0) {
                    a[i + 1] += a[i];
                    a[i] = 0;
                }
                if (a[i] < 0) {
                    a[i + 1] -= abs(a[i]);
                    a[i] = 0;
                }
                ans++;
            } else continue;
        }
        cout << ans;
        return 0;
    }
    cout << ans;
}