#include <bits/stdc++.h>
using namespace std;
int v[9], ans = 0;
bool f = 0;
int dfs(int n) {
    if (n == 1) {
        if (v[4] == 24) {
            f = 1;
        }
        return 0;
    }
    int vv = v[4 - n + 1];
    int vvv = v[4 - n + 2];
    v[4 - n + 2] += vv;
    dfs(n - 1);
    v[4 - n + 2] = vvv, v[4 - n + 1] = vv;
    if (f) return 0;
    v[4 - n + 2] -= vv;
    dfs(n - 1);
    v[4 - n + 2] = vvv, v[4 - n + 1] = vv;
    if (f) return 0;
    v[4 - n + 2] *= vv;
    dfs(n - 1);
    v[4 - n + 2] = vvv, v[4 - n + 1] = vv;
    return 0;
}
int main() {
    int a;
    cin >> a;
    for (int i = 0; i < a; i++) {
        cin >> v[1] >> v[2] >> v[3] >> v[4];
        f = 0;
        dfs(4);
        ans += f;
    }
    cout << ans;
}