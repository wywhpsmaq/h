#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return (a.first == b.first) ? a.second < b.second : a.first < b.first;
}
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x,y});
    }
    sort(v.begin(), v.end(), cmp);
    int ans = 0;
    vector<pair<int, int>> p;
    for (int i = 0; i < n; i++) {
        bool f = 1;
        for (auto& j : p) {
            if (j.first <= v[i].first && j.second <= v[i].second) {
                j.first = v[i].first;
                j.second = v[i].second;
                f = 0;
                break;
            }
        }
        if (f) {
            ans++;
            p.push_back(v[i]);
        }
    }
    cout << ans;
}