#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> vis(100001, false);
    queue<pair<int, int>> q;
    q.push({n, 0});
    vis[n] = true;
    while (!q.empty()) {
        auto [x, step] = q.front();
        q.pop();
        if (x == m) {
            cout << step;
            return 0;
        }
        if (x - 1 >= 0 && !vis[x - 1]) {
            vis[x - 1] = true;
            q.push({x - 1, step + 1});
        }
        if (x + 1 <= 100000 && !vis[x + 1]) {
            vis[x + 1] = true;
            q.push({x + 1, step + 1});
        }
        if (x * 2 <= 100000 && !vis[x * 2]) {
            vis[x * 2] = true;
            q.push({x * 2, step + 1});
        }
    }
}