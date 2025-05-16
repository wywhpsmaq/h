#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> v(n + m, 0);
    queue<pair<int, int>> q;
    q.push({n, 0});
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        if (p.first == m) {
            cout << p.second;
            return 0;
        }
        if (p.first - 1 >= 0 && !v[p.first - 1]) {
            q.push({p.first - 1, p.second + 1});
            v[p.first - 1] = 1;
        }
        if (p.first + 1 <= 100000 && p.first < m && !v[p.first + 1]) {
            q.push({p.first + 1, p.second + 1});
            v[p.first + 1] = 1;
        }
        if (p.first * 2 <= 100000 && p.first < m && !v[p.first * 2]) {
            q.push({p.first * 2, p.second + 1});
            v[p.first * 2] = 1;
        }
    }
}