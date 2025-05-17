#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> v[100086];
bool vis[100086];
int ans = 0;
void dfs(int x, int num) {
    vis[x] = 1;
    if (num > m) return;
    if (x != 1) ans++;
    for (auto i : v[x]) {
        if (!vis[i]) {
            dfs(i, num + 1);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 0);
    cout << ans;
}