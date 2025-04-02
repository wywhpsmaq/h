#include <bits/stdc++.h>
using namespace std;
vector<int> v;
bool f(long long k, int m) {
    int b = 0;
    long long a = 0;
    for (int i = 0; i < v.size(); i++) {
        if (a < v[i]) {
            if (b >= m) {
                return false;
            }
            a = k;
            b++;
        }
        if (a < v[i]) {
            return false;
        }
        a -= v[i];
    }
    return true;
}
int main() {
    int n, m;
    cin >> n >> m;
    v.resize(n);
    int mp = 0;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        mp = max(mp, v[i]);
        sum += v[i];
    }
    long long l = mp, r = sum;
    while (l < r) {
        long long mid = l + (r - l) / 2;
        if (f(mid, m)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l;
    return 0;
}