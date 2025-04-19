#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int f(int a) {
    int l = 0, r = v.size(), ans = INT_MAX;
    while (l < r) {
        int mid = (l + r) / 2;
        ans = min(ans, abs(a - v[mid]));
        if (v[mid] < a) {
            l = mid + 1;
        } else r = mid;
    }
    return ans;
}
int main() {
    int a, b;
    cin >> a >> b;
    v.resize(a);
    for (int i = 0; i < a; i++) {
        cin >> v[i];
    }
    int x, ans = 0;
    sort(v.begin(), v.end());
    for (int i = 0; i < b; i++) {
        cin >> x;
        ans += f(x);
    }
    cout << ans;
}