#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int a[114514];
    int dis[114514] = {};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dis[i] = a[i];
    }
    vector<vector<int>> p(n + 1);
    vector<int> v(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        //p[y].push_back(x);
        v[y]++;
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; ++i) {
        if (v[i] == 0) { q.push(i); }
    }
    vector<int> ans;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        ans.push_back(u);
        for (int i : p[u]) {
            dis[i] = max(dis[i], dis[u] + a[i]);
            v[i]--;
            if (v[i] == 0) q.push(i);
        }
    }
    int z_ans = 0;
    for (int i = 1; i <= n; i++) {
        z_ans = max(z_ans, dis[i]);
    }
    cout << z_ans;
}