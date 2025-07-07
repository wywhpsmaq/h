#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<pair<int, int>> g[114514];
int f() {
    queue<pair<int, int>> q;
    q.push({1,0});
    while (!q.empty()) {
        auto a = q.front();
        for (auto i : g[a.first]) {

        }
    }
}
int main() {
    int w;
    cin >> w;
    while (w--) {
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            g[x].push_back({y + 1,z});
            g[y].push_back({x + 1,z});
        }
        if (f()) cout << "true\n";
        else cout << "fales\n";
    }
}