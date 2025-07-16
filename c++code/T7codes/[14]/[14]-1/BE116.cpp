#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}
int main() {
    int n, s;
    cin >> n >> s;
    int a, b;
    cin >> a >> b;
    vector < pair<int, int>> p;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p.push_back({x, y});
    }
    sort(p.begin(), p.end(), cmp);
    int i = 0;
    int ans = 0;
    while (i < n) {
        if (p[i].first <= a + b && s >= p[i].second) {
            ans++;
            s -= p[i].second;
        }
        i++;
    }
    cout << ans;
}