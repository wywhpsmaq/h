#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int a[114514];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    long long ans = 0;
    int l = 0, r = n - 1, num = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            ans += abs(a[r] - num) * abs(a[r] - num);
            num = a[r];
            r--;
        } else {
            ans += abs(num - a[l]) * abs(num - a[l]);
            num = a[l];
            l++;
        }
    }
    cout << ans;
}