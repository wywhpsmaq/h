#include<bits/stdc++.h>
using namespace std;
struct uu {
    int t, a;
};
bool cmp(const uu& a, const uu& b) {
    return a.t < b.t;
}
int main() {
    int n;
    cin >> n;
    vector<uu> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].t;
        p[i].a = i + 1;
    }
    sort(p.begin(), p.end(), cmp);
    for (int i = 0; i < n; ++i) {
        cout << p[i].a;
        if (i != n - 1) cout << " ";
    }
    cout << '\n';
    long long sum = 0, num = 0;
    for (int i = 0; i < n - 1; ++i) {
        num += p[i].t;
        sum += num;
    }
    double ans = (double)sum / n;
    printf("%.2f", ans);
    return 0;
}