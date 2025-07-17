#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> p;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p.push_back({x,y});
    }
    int len = 0;
    int ans = 0;
    int a[114514];
    sort(p.begin(), p.end(), cmp);
    for (int i = 0; i < n; i++) {
        bool f = 1;
        for (int j = 0; j < len; j++) {
            if (a[j] < p[i].first) {
                a[j] = p[i].second;
                f = 0;
                break;
            }
        }
        if (f) {
            a[len++] = p[i].second;
            ans++;
        }
    }
    cout << ans;
}