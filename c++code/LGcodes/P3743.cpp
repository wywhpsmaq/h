#include<bits/stdc++.h>
using namespace std;
#define itn int
#define int long long
int n, p, x, y, num;
vector<pair<int, int>> v;
int ch(double a) {
    double ans = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first * a <= v[i].second) continue;
        ans += (v[i].first * a - v[i].second);
    }
    return ans <= a * p;
}
signed main() {
    ios::sync_with_stdio(false);
    cin >> n >> p;
    max(n,p);
    for (itn i = 0; i < n; i++) {
        cin >> x >> y;
        num += y;
        v.push_back(make_pair(x, y));
    }
    if (num <= p) {
        cout << -1;
        return 0;
    }
    double l = 0, r = 100000;
    while (fabs(l - r) > 0.00000000001) {
        double mid = (l + r) / 2;
        if (ch(mid)) l = mid;
        else r = mid;
    }
    printf("%f", l);
}