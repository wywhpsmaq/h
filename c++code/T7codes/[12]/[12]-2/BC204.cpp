#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> d;
vector<int> p[114514];
vector<int> v_;
vector<bool> v;
vector<int> sum;
int n;
int ml, mj;
void dfs(int a, int num) {
    v[a] = true;
    if (num > ml) {
        ml = num, mj = a;
        v_ = sum;
    }
    for (auto x : p[a]) {
        if (!v[x]) {
            sum.push_back(x);
            dfs(x, num + 1);
            sum.pop_back();
        }
    }
}
int m666() {
    for (auto x : v_) {
        d[x].second++;
    }
    return 0;
}
int main() {
    cin >> n;
    d.push_back({0, 0});
    d.push_back({0, 0});
    for (int i = 1; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        p[x].push_back(y);
        p[y].push_back(x);
        d.push_back({z, 0});
    }
    d.push_back({0, 0});
    for (int i = 2; i <= n; ++i) {
        sum.resize(0);
        v.assign(n + 10, 0);
        sum.push_back(i);
        dfs(i, 0);
        m666();
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i].second == n - 1) {
            ans += d[i].first;
        }
    }
    cout << ans;
}