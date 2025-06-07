#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int sz[MAXN], centroid[MAXN], n, q, fa[MAXN];
vector<int> t[MAXN];

void calc_size(int u, int f) {
    sz[u] = 1;
    for (int v : t[u]) {
        if (v == f) continue;
        calc_size(v, u);
        sz[u] += sz[v];
    }
}

void find_centroid(int u, int f) {
    int c = u;
    while (true) {
        bool found = false;
        for (int v : t[c]) {
            if (v == f) continue;
            if (sz[v] > sz[u] / 2) {
                c = v;
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    centroid[u] = c;
    for (int v : t[u]) {
        if (v == f) continue;
        find_centroid(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
        t[fa[i]].push_back(i);
        t[i].push_back(fa[i]);
    }
    calc_size(1, 0);
    find_centroid(1, 0);
    while (q--) {
        int x;
        cin >> x;
        cout << centroid[x] << '\n';
    }
    return 0;
}