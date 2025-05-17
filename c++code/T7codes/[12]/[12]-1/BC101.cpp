#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int p[999] = {};
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        p[b] = a;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            ans++;
        }
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            cout << i << " ";
        }
    }
}