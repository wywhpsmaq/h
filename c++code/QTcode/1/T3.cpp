#include <bits/stdc++.h>
using namespace std;
vector<long long> t;
int n;
void it(int size) {
    n = 1;
    while (n < size) n <<= 1;
    t.assign(2 * n, LLONG_MIN);
}
void u(int o, long long v) {
    o += n;
    if (t[o] >= v) return;
    t[o] = v;
    for (int i = o>>1; i >= 1; i >>= 1) {
        long long v = max(t[2 * i], t[2 * i + 1]);
        if (t[i] == v) break;
        t[i] = v;
    }
}
long long q(int l, int r) {
    l += n, r += n;
    long long e = LLONG_MIN;
    while (l <= r) {
        if (l % 2 == 1) {
            e = max(e, t[l]);
            l++;
        }
        if (r % 2 == 0) {
            e = max(e, t[r]);
            r--;
        }
        l >>= 1;
        r >>= 1;
    }
    return e;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> s(n), p(n), a(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<long long> p_(p.begin(), p.end());
    sort(p_.begin(), p_.end());
    p_.erase(unique(p_.begin(), p_.end()), p_.end());
    int m = p_.size();
    it(m);
    for (int i = 0; i < n; ++i) {
        int x = lower_bound(p_.begin(), p_.end(), p[i]) - p_.begin();
        long long v = q(0, x);
        long long te = max(s[i] + p[i], (v == LLONG_MIN ? LLONG_MIN : v + p[i]));
        te = max(te, s[i] + p[i]);
        long long ci = te + a[i];
        cout << ci << '\n';
        u(x, ci - p[i]);
    }
    return 0;
}