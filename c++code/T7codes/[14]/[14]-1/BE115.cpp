#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}
int main() {
    int n, m, k, l, q;
    cin >> n >> m >> k >> l >> q;
    vector<pair<int, int>> h(n + 1);
    vector<pair<int, int>> s(m + 1);
    for (int i = 0; i < q; i++) {
        int x, y, x1, y1;
        cin >> x >> y >> x1 >> y1;
        if (x == x1) {
            s[min(y, y1)].first++, s[min(y, y1)].second = min(y, y1);
        } else {
            h[min(x, x1)].first++, h[min(x, x1)].second = min(x, x1);
        }
    }
    sort(h.begin(), h.end(), cmp);
    sort(s.begin(), s.end(), cmp);
    for (int i = 0; i < k; i++) {
        cout << h[i].second << " ";
    }
    cout << '\n';
    for (int i = 0; i < l; i++) {
        cout << s[i].second << " ";
    }
}