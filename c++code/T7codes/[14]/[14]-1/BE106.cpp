#include<bits/stdc++.h>
using namespace std;
map<int, int> p;
priority_queue<int, vector<int>, greater<int> > q[1145144];
int a[1145144], k, s;
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        if (p[a[i]] == 0)p[a[i]] = ++k;
        if (p[a[i] - 1] == 0 || q[p[a[i] - 1]].size() == 0) {
            q[p[a[i]]].push(1);
        } else {
            s = q[p[a[i] - 1]].top() + 1;
            q[p[a[i] - 1]].pop();
            q[p[a[i]]].push(s);
        }
    }
    int ans = 1145144;
    for (int i = 1; i <= n; ++i) {
        if (q[p[a[i]]].size() > 0) {
            ans = min(ans, q[p[a[i]]].top());
        }
    }
    cout << ans;
    return 0;
}
