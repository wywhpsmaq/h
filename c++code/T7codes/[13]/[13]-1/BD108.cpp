#include<bits/stdc++.h>
using namespace std;
int k, n, m;
vector<int> p[114514];
int nn[114514];
vector<bool> v(114514);
int dfs(int x) {
    v[x] = 1;
    nn[x]++;
    for (int i : p[x]) {
        if (!v[i]) dfs(i);
    }
    return 0;
}
int main() {
    cin >> k >> n >> m;
    int a[114514];
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
    }
    for (int i = 0; i < k; i++) {
        fill(v.begin(), v.begin() + k + 1, 0);
        dfs(a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (nn[i] == k) {
            ans++;
        }
    }
    cout << ans;
}