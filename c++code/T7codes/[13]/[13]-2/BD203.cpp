#include<bits/stdc++.h>
using namespace std;
struct uu {
    int r, to, w;
};
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<uu> v(m);
    for (int i = 0; i < m; ++i) {
        cin >> v[i].r >> v[i].to >> v[i].w;
    }
    vector<int> dist(n + 1, 0x3f3f3f3f);
    dist[1] = 0;
    for (int i = 0; i < k; ++i) {
        vector<int> last = dist;
        for (const auto& e : v) {
            if (last[e.r] < 0x3f3f3f3f) {
                dist[e.to] = min(dist[e.to], last[e.r] + e.w);
            }
        }
    }
    if (dist[n] > 0x3f3f3f3f / 2) cout << "impossible" << endl;
    else cout << dist[n] << endl;

    return 0;
}