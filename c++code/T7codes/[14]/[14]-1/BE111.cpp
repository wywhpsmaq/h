#include<bits/stdc++.h>
using namespace std;
bool cmp(int a, int b) {
    return a > b;
}
int main() {
    int m, s, c;
    cin >> m >> s >> c;
    if (c <= m) {
        cout << c;
        return 0;
    }
    vector<int> v(c);
    for (int i = 0; i < c; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int ans = v[c - 1] - v[0] + 1;
    vector<int> b(c - 1);

    for (int i = 0; i < c - 1; i++) {
        b[i] = v[i + 1] - v[i] - 1;
    }
    sort(b.begin(), b.end(), cmp);
    for (int i = 0; i < m - 1; i++) {
        ans -= b[i];
    }
    cout << ans;
}