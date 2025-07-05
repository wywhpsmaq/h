#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int fa[114514], sz[114514];
vector<int> g[114514];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int cnt, x;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            cin >> x;
            g[i].push_back(x);
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
        for (int i = k + 1; i <= n; ++i) {
            for (int v : g[i]) {
                if (v > k) {
                    int fi = find(i), fv = find(v);
                    if (fi != fv) {
                        fa[fi] = fv;
                        sz[fv] += sz[fi];
                    }
                }
            }
        }
        int mx = 0;
        for (int i = k + 1; i <= n; ++i) {
            if (find(i) == i) mx = max(mx, sz[i]);
        }
        if (mx <= n / 2) {
            cout << k << endl;
            return 0;
        }
    }
    return 0;
}