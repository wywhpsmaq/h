#include <bits/stdc++.h>
using namespace std;
int h[999], l[999], zd[999], fd[999];
int a, b, ans, num = 0;
void dfs(int n) {
    if (n == a + 1) {
        ans++;
        if (num < 3) {
            num++;
            for (int i = 1; i <= a; i++)
                cout << h[i] << " ";
            cout << '\n';
        }
        return;
    }
    for (int i = 1; i <= a; i++) {
        if (l[i] || zd[n + i] || fd[n - i + a]) continue;
        l[i] = zd[n + i] = fd[n - i + a] = 1;
        h[n] = i;
        dfs(n + 1);
        l[i] = zd[n + i] = fd[n - i + a] = 0;
    }
}
int main() {
    cin >> a;
    dfs(1);
    cout << ans;
}