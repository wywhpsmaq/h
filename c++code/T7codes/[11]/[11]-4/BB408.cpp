#include <bits/stdc++.h>
using namespace std;
int n, w, ans = 20;
vector<int> v;
vector<int> p;
void dfs(int x) {
    if (p.size() >= ans) return;
    if (x == n) {
        ans = min(ans, (int)p.size());
        return;
    }
    for (int i = 0; i < p.size(); ++i) {
        if (p[i] + v[x] <= w) {
            p[i] += v[x];
            dfs(x + 1);
            p[i] -= v[x];
        }
    }
    p.push_back(v[x]);
    dfs(x + 1);
    p.pop_back();
}
int main() {
    cin >> n >> w;
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v.rbegin(), v.rend());
    dfs(0);
    cout << ans;
    return 0;
}