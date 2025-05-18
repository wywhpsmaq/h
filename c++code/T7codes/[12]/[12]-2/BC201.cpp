#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> p;
vector<bool> v;
int n;
int ml, mj;
void dfs(int a, int num) {
    v[a] = true;
    if (num > ml) {
        ml = num, mj = a;
    }
    for (auto [x, y] : p[a]) {
        if (!v[x]) {
            dfs(x, num + y);
        }
    }
}
int main() {
    cin >> n;
    p.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        p[a].push_back({b, c});
        p[b].push_back({a, c});
    }
    v.assign(n + 1, false);
    ml = 0, mj = 0;
    dfs(1, 0);
    v.assign(n + 1, false);
    dfs(mj, 0);
    cout << ml;
}