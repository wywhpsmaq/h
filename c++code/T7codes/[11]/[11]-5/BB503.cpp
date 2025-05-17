#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> p(m, vector<int>(n));
    vector<int> gd(m, 0), kd(m, 0);
    queue<pair<int, int>> q;
    unordered_set<int> v;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> p[i][j];
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[i][j] == 1) {
                gd[i] |= (1 << j);
            } else if (p[i][j] == -1) {
                kd[i] |= (1 << j);
            }
        }
    }
    int s = (1 << n) - 1;
    q.push({s, 0});
    v.insert(s);
    while (!q.empty()) {
        auto [d, t] = q.front();
        q.pop();
        if (d == 0) {
            cout << t;
            return 0;
        }
        for (int i = 0; i < m; ++i) {
            int nd = d;
            nd &= ~gd[i];
            nd |= kd[i];
            if (!v.count(nd)) {
                v.insert(nd);
                q.push({nd, t + 1});
            }
        }
    }
    cout << -1;
    return 0;
}