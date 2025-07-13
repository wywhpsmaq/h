#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<int> p[114514];
int bfs(int a) {
    int ans = 1;
    queue<int> q;
    vector<bool> v(n + 1, 0);
    v[a] = 1;
    q.push(a);
    while (!q.empty()) {
        int x = q.front();
        for (int i : p[x]) {
            if (!v[i]) { ans++; q.push(i); v[i] = 1; }
        }
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
    }
    for (int i = 1; i <= n; i++) {
        cout << bfs(i) << '\n';
    }
}