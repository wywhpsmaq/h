#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int t, w;
        cin >> t >> w;
        v.push_back({t, w});
    }
    sort(v.begin(), v.end());
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        if ((int)q.size() < v[i].first) {
            q.push(v[i].second);
        } else if (q.top() < v[i].second) {
            q.pop();
            q.push(v[i].second);
        }
    }
    long long ans = 0;
    while (!q.empty()) {
        ans += q.top();
        q.pop();
    }
    cout << ans;
}