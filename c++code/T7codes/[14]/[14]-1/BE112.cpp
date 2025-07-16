#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int p[114514], s[114514] = {};
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> p[i];
        if (i != 1) s[i] = min(s[i], s[i - 1] + m);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += p[i] * s[i];
    }
    cout << ans;
}