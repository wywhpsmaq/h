#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> t;
int k, ans;
int n;
int dfs(int u, int fa) {
    int sum = 1;
    for (int v : t[u]) {
        if (v == fa) continue;
        sum += dfs(v, u);
    }
    if (sum % k == 0) ans++;
    return sum % k;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t_;
    cin >> t_;
    while (t_--) {
        cin >> n >> k;
        t.assign(n + 1, vector<int>());
        for (int i = 1; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            t[a].push_back(b);
            t[b].push_back(a);
        }
        if (n % k != 0) {
            cout << "NO\n";
            continue;
        }
        ans = 0;
        int num = dfs(1, 0);
        if (num == 0 && ans - 1 == n / k - 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}