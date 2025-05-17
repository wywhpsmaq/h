#include <bits/stdc++.h>
using namespace std;
vector<int> t[110];
int v[110], s[110];
void dfs(int u, int p) {
    s[u] = 1;
    for (int v : t[u]) {
        if (v != p) {
            dfs(v, u);
            s[u] += s[v];
        }
    }
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> v[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        t[a].push_back(b);
        t[b].push_back(a);
    }
    dfs(1, -1);
    int ms = 0, my = 0;
    for (int ch : t[1]) {
        ms = max(ms, s[ch]);
    }
    for (int i = 1; i <= n; ++i) {
        my = max(my, v[i] * s[i]);
    }
    cout << ms << " " << my;
    return 0;
}
