#include <bits/stdc++.h>
using namespace std;
#define itn int
#define inr int
//#define int long long
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m,s, t,k;
    cin >> n >> m;
    vector<pair<int,int>> v[n+1], vv[n+1];
    for (int i = 0; i < m; ++i) {
        int x,y; int z;
        cin >> x >> y >> z;
        v[x].emplace_back(y, z);
        vv[y].emplace_back(x, z);
    }
    cin >> s >> t >> k;
    vector h(n+1, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    h[t] = 0;
    q.emplace(0, t);
    while (!q.empty()) {
        auto [x, y] = q.top(); q.pop();
        // if (x != h[y]) continue;
        for (auto i : vv[y]) {
            if (h[i.first] > x + i.second) {
                h[i.first] = x + i.second;
                q.emplace(h[i.first], i.first);
            }
        }
    }
    if (h[s] == INT_MAX && s != t) {
        cout << -1;
        return 0;
    }
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.emplace(h[s], 0LL, s);
    int ff = 0;
    while (!pq.empty()) {
        auto [x, y, z] = pq.top(); pq.pop();
        if (h[z] == INT_MAX && z != t) continue;
        if (z == t) {
            if (!(z == s && y == 0)) {
                ff++;
                if (ff == k) {
                    cout << y;
                    return 0;
                }
            }
        }
        for (auto i : v[z]) {
            if (h[i.first] == INT_MAX) continue;
            pq.emplace(y+i.second+h[i.first], y+i.second, i.first);
        }
    }
    cout << -1 << "\n";
}