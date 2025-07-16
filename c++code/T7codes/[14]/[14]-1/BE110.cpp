#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}
int main() {
    vector < pair<int, int>> p;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        p.push_back({x,y});
    }
    sort(p.begin(), p.end(), cmp);
    int ans = 0;
    int i = 0;
    while (n != 0) {
        if (n >= p[i].second) {
            ans += p[i].first * p[i].second;
            n -= p[i].second;
        } else {
            ans += p[i].first * n;
            n = 0;
        }
        i++;
    }
    cout << ans;
}