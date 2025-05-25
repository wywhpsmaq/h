#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    vector<double> c(n, 0.0);
    vector<int> ch = a;
    vector<bool> p(n, true);
    while (true) {
        vector<int> x;
        for (int i = 0; i < n; ++i)
            if (ch[i] > 0) x.push_back(i);
        if (x.size() <= 1) break;
        int d = INT_MAX;
        for (int i : x) d = min(d, ch[i]);
        double o = 0;
        for (int i : x) {
            o += d;
            ch[i] -= d;
        }
        int mb = -1;
        for (int i : x) mb = max(mb, b[i]);
        vector<int> w;
        for (int i : x)
            if (b[i] == mb) w.push_back(i);
        double wa = o / w.size();
        for (int i : w) c[i] += wa;
    }
    for (int i = 0; i < n; ++i) {
        if (ch[i] > 0) c[i] += ch[i];
    }
    for (int i = 0; i < n; ++i) cout << c[i] << '\n';
    return 0;
}