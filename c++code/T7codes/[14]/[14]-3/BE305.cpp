#include<bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    priority_queue<long long, vector<long long>, greater<long long>> q;
    long long ans = 0;
    for (long long p : p) {
        q.push(p);
        if (p > q.top()) {
            long long num = q.top();
            q.pop();
            ans += p - num;
            q.push(p);
        }
    }
    cout << ans;
    return 0;
}