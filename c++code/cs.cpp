#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> p;
int nn, x, y, ans = -1;
void dfs(int n, int m, int x) {
    if (n > nn) return;
    ans = max(ans, x);
    if (m >= p[n].first) dfs(n + 1, m - p[n].first + 1, x + p[n].second);
    dfs(n + 1, m + 1, x);
}
int main() {
    cin >> nn;
    for (int i = 0; i < nn; i++) {
        cin >> x >> y;
        p.push_back({x, y});
    }
    dfs(0, 1, 0);
    cout << ans;
}