#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        v.push_back(a);
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 0; i < n / 2; i++) {
        ans = max(ans, v[i] + v[n - i - 1]);
    }
    cout << ans;
}