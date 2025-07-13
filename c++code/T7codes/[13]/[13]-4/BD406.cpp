#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int pp[114][114];
    vector<int> dis(n + 1, -1);
    vector<vector<int>> p(n + 1);
    vector<int> v(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        pp[y][x] = 1;
        //p[x].push_back(y);    
        if (!pp[y][x]) { p[y].push_back(x); v[x]++; }
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; ++i) {
        if (v[i] == 0) { q.push(i); dis[i] = 1; }
    }
    vector<int> ans;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        ans.push_back(u);
        for (int i : p[u]) {
            v[i]--;
            dis[i] += dis[u];
            if (v[i] == 0) { q.push(i); }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << '\n';
    }
}