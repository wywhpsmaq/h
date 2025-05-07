#include <bits/stdc++.h>
using namespace std;
bool f(vector<long long>& v, long long  l, long long m, long long n) {
    long long a = 0;
    long long b = 0;
    for (long long r : v) {
        if (r - a < n) {
            b++;
            if (b > m) return false;
        } else {
            a = r;
        }
    }
    if (l - a < n) return false;
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long l, n, m;
    cin >> l >> n >> m;
    vector<long long> v(n);
    for (long long i = 0; i < n; i++) {
        cin >> v[i];
    }
    long long le = 1, ri = l;
    long long ans = 0;
    while (le <= ri) {
        long long mid = le + (ri - le) / 2;

        if (f(v, l, m, mid)) {
            ans = mid;
            le = mid + 1;
        } else {
            ri = mid - 1;
        }
    }
    cout << ans;
}