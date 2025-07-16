#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int a[114514] = {};
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    sort(a, a + m);
    int l = 0, r = m - 1;
    int ans = 0;
    while (1) {
        if (l >= r) {
            if (l == r) cout << ans + 1;
            else cout << ans;
            return 0;
        }
        if (a[l] + a[r] <= n) ans++, l++, r--;
        else ans++, r--;
    }
}