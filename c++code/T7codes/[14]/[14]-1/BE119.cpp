#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int a[114514] = {}, b[114514] = {};
    int mm = 0, mn = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mm = max(mm, a[i]);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        mn = max(mn, b[i]);
    }
    if (mn < mm) {
        cout << "you died!";
        return 0;
    }
    sort(a, a + n);
    sort(b, b + m);
    int l = 0, l1 = 0;
    int ans = 0;
    while (1) {
        if (b[l1] >= a[l]) {
            l++;
            ans += b[l1];
        } else {
            l1++;
        }
        if (l == n - 1) {
            cout << ans;
            return 0;
        }
    }
}