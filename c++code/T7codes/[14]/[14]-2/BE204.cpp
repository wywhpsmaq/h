#include<bits/stdc++.h>
using namespace std;
struct uu {
    int w, f;
};
int main() {
    int n;
    cin >> n;
    vector<uu> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].w >> p[i].f;
    }
    sort(p.begin(), p.end(), [](const uu &a, const uu &b) {
        return a.w + a.f < b.w + b.f;
    });

    long long num = 0;
    long long ans = -1e18;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, num - p[i].f);
        num += p[i].w;
    }
    cout << ans << endl;
    return 0;
}