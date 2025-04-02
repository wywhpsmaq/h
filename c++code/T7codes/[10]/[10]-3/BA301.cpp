#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio (false);
    cin . tie (nullptr);
    cout . tie (nullptr);
    int a, m;
    cin >> a >> m;
    vector<int> n(a);
    for (int i = 0; i < a; ++i) {
        cin >> n[i];
    }
    vector<int> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    for (int i : p) {
        auto it = lower_bound(n.begin(), n.end(), i);
        if (it != n.end() && *it == i) {
            cout << distance(n.begin(), it) + 1 << " ";
        } else {
            cout << "-1 ";
        }
    }
    return 0;
}
