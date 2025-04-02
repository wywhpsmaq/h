#include <bits/stdc++.h>
using namespace std;
vector<int> ar;
long long ff(int l, int mid, int r) {
    int i = l, j = mid + 1;
    vector<int> a;
    long long c = 0;
    while (i <= mid && j <= r) {
        if (ar[i] <= ar[j]) {
            a.push_back(ar[i++]);
        } else {
            a.push_back(ar[j++]);
            c += (mid - i + 1);
        }
    }
    while (i <= mid) {
        a.push_back(ar[i++]);
    }
    while (j <= r) {
        a.push_back(ar[j++]);
    }
    for (int k = l; k <= r; k++) {
        ar[k] = a[k - l];
    }
    return c;
}
long long f(int l, int r) {
    long long c = 0;
    if (l < r) {
        int mid = l + (r - l) / 2;
        c += f(l, mid);
        c += f(mid + 1, r);
        c += ff(l, mid, r);
    }
    return c;
}
int main() {
    int n;
    cin >> n;
    ar.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
    }
    long long ans = f(0, n - 1);
    cout << ans;
    return 0;
}