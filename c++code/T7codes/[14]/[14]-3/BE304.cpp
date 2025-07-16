#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int,int> a, pair<int,int> b) {
    return a.second > b.second;
}
int main() {
    int n;
    cin >> n;
    vector<pair<int,int>> p(n);
    int num = 0;
    for(int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        num = max(num, p[i].first);
    }
    sort(p.begin(), p.end(), cmp);
    vector<bool> v(num, false);
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = min(num - 1, p[i].first - 1); j >= 0; j--) {
            if(!v[j]) {
                v[j] = true;
                ans += p[i].second;
                break;
            }
        }
    }
    cout << ans;
    return 0;
}