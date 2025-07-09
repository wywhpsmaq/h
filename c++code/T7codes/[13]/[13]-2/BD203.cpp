#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, pair<int, int>>> v(m);
    for (int i = 0; i < m; ++i) {
        cin >> v[i].first >> v[i].second.first >> v[i].second.second;
    }
    vector<int> dist(n + 1, 0x3f3f3f3f);
    dist[1] = 0;
    for (int i = 0; i < k; ++i) {
        vector<int> last = dist;
        for (auto e : v) {
            if (last[e.first] < 0x3f3f3f3f) {
                dist[e.second.first] = min(dist[e.second.first], last[e.first] + e.second.second);
            }
        }
    }
    if (dist[n] > 0x3f3f3f3f / 2) cout << "impossible" << endl;
    else cout << dist[n] << endl;

    return 0;
}