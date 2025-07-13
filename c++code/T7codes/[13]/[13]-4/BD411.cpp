#include <bits/stdc++.h>
using namespace std;
int n, m, d[6000], c[6000];
int a, b, f[6000], ans;
vector<int> e[6000];
queue<int> q;
int main () {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        e[a].push_back(b);
        c[a]++;
        d[b]++;
    }
    for (int i = 1; i <= n; i++) {
        if (d[i] == 0) {
            f[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int g = q.front();
        q.pop();
        for (int j : e[g]) {
            (f[j] += f[g]) %= 80112002;
            d[j]--;
            if (d[j] == 0) q.push(j);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (c[i] == 0) {
            (ans += f[i]) %= 80112002;
        }
    }
    cout << ans;
}