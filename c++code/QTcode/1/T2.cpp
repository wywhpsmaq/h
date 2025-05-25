#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) p[i] = {a[i], i};
    sort(p.begin(), p.end());
    vector<int> mb(n), cb(n);
    mb[n - 1] = b[p[n - 1].second];
    cb[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        int ub = b[p[i].second];
        if (ub > mb[i + 1]) {
            mb[i] = ub;
            cb[i] = 1;
        } else if (ub == mb[i + 1]) {
            mb[i] = mb[i + 1];
            cb[i] = cb[i + 1] + 1;
        } else {
            mb[i] = mb[i + 1];
            cb[i] = cb[i + 1];
        }
    }
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[p[i].second] = i;
    }
    double sum = 0.0;
    unordered_map<int, vector<pair<int, double>>> mp;
    for (int i = 0; i < n; ++i) {
        if (sum >= p[i].first) continue;
        double d = p[i].first - sum;
        int r = n - i;
        double v = (d * r) / cb[i];
        mp[mb[i]].emplace_back(i, v);
        sum = p[i].first;
    }
    vector<double> c(n, 0.0);
    for (auto &[mv, vec] : mp) {
        vector<int> ks;
        vector<double> vs;
        for (auto &[k, v] : vec) {
            ks.push_back(k);
            vs.push_back(v);
        }
        for (int i = 1; i < vs.size(); ++i) {
            vs[i] += vs[i - 1];
        }
        for (int j = 0; j < n; ++j) {
            if (b[j] != mv) continue;
            int kj = pos[j];
            auto it = upper_bound(ks.begin(), ks.end(), kj);
            if (it == ks.begin()) continue;
            int x = prev(it) - ks.begin();
            c[j] += vs[x];
        }
    }
    for (auto x : c) cout << x << '\n';
    return 0;
}