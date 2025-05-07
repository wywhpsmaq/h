#include <bits/stdc++.h>
using namespace std;
int n, l, r;
int p[50];
int ans = 0;
void dfs(int x, int num) {
    if (num > r) return;
    int rs = 0;
    for (int i = x; i < n; i++) rs += p[i];
    if (num + rs < l) return;
    if (x == n) {
        if (l <= num && num <= r) ans++;
        return;
    }
    dfs(x + 1, num);
    dfs(x + 1, num + p[x]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> l >> r;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    dfs(0, 0);
    cout << ans << '\n';
}