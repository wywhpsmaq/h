#include<bits/stdc++.h>
using namespace std;
vector<int> p[114514];
bool vi[114514];
int n, m;
void dfs(int u) {
    vi[u] = true;
    cout << u << " ";
    for (int v : p[u]) {
        if (!vi[v]) {
            dfs(v);
        }
    }
}
void bfs(int s) {
    fill(vi, vi + 114514, false);
    queue<int> q;
    q.push(s);
    vi[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v : p[u]) {
            if (!vi[v]) {
                vi[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        sort(p[i].begin(), p[i].end());
    }
    fill(vi, vi + 114514, false);
    dfs(1);
    cout << '\n';
    bfs(1);
    return 0;
}