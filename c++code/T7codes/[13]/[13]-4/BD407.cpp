#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> dis(n + 1, 0);
    vector<vector<pair<int, int>>> p(n + 1);
    vector<int> v(n + 1, 0);
    int a[114514];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dis[i] = a[i];
    }
    for (int i = 0; i < c; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        p[x].push_back({y,z});
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
        for (auto i : p[u]) {
            v[i.first]--;
            dis[i.first] = max(dis[i.first], dis[u] + i.second);
            if (v[i.first] == 0) { q.push(i.first); }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << '\n';
    }
}