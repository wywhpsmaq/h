#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1);
    int p[999] = {};
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        a[x].push_back(y);
        p[y]++;
    }
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            cout << i << '\n';
            break;
        }
    }
    int ans = 0, num = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i].size() > ans) {
            ans = a[i].size();
            num = i;
        }
    }
    cout << num << '\n';
    for (int i = 0; i < a[num].size(); i++) {
        cout << a[num][i] << " ";
    }
}