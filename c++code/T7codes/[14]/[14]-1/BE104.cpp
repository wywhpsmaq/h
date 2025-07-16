#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> v;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        v.push_back(x);
    }
    for (int i = 0; i < n - 1; i++) {
        if (v[i] + v[i + 1] > m) {
            int num = v[i] + v[i + 1] - m;
            ans += num;
            if (v[i + 1] >= num) {
                v[i + 1] -= num;
            } else {
                num -= v[i + 1];
                v[i + 1] = 0;
                v[i] -= num;
            }
        }
    }
    cout << ans;
}