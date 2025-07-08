#include<bits/stdc++.h>
using namespace std;
vector<int> p[114514];
vector<bool> v;
vector<int> vv;
vector<int> ans(114514);
int n, m;
int x, y;
int num;
int f[114514] = {};
int dfs(int a) {
    if (a == y) {
        num++;
        for (int i = 0; i < vv.size() - 1; i++) {
            ans[vv[i]]++;
        }
        return 0;
    }
    for (auto i : p[a]) {
        if (!v[i] && !f[i]) {
            v[i] = 1;
            vv.push_back(i);
            dfs(i);
            v[i] = 0;
            vv.pop_back();
        }
    }
    return 0;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    cin >> x >> y;
    v.assign(n + 1, 0);
    vector<int> o;
    cin >> x >> y;
    queue<pair<pair<int, int>, vector<int>>> q;
    o.push_back(x);
    q.push({{x,1},o});
    while (!q.empty()) {
        auto a = q.front();
        if (a.first.first == y) {
            o = a.second;
            break;
        }
        q.pop();
        for (int i : p[a.first.first]) {
            if (!v[i]) {
                v[i] = 1;
                a.second.push_back(i);
                q.push({{i,a.first.second + 1},a.second});
                a.second.pop_back();
            }
        }
    }
    for (int i = 0; i < o.size(); i++) {
        ans[vv[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0) {
            p[i].clear();
        }
    }
    ans.assign(n + 10, 0);
    v[x] = 1;
    dfs(x);
    int ans_ = 0;
    for (int i = 0; i < n; i++) {
        if (ans[i] == num) {
            ans_++;
        }
    }
    cout << ans_;
}