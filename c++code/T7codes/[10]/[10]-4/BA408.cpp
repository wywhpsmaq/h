#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int f(int k, int n, int d) {
    int a = v[0], b = n - 1;
    for (int i = 1; i < d; i++) {
        if (v[i] - a >= k) {
            b--;
            a = v[i];
        }
        if (b <= 0) return 1;
    }
    return b <= 0;
}
int main() {
    int a, b, ans = -1;
    cin >> a >> b;
    v.resize(a);
    for (int i = 0; i < a; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int l = 1, r = ((v[a - 1] - v[0]) / b) + 2;
    while (l < r) {
        int mid = (l + r) / 2;
        if (f(mid, b, a)) {
            ans = max(ans, mid);
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << ans;
}