#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int, int>> edges;
vector<vector<int>> adj;

void build_adj(const vector<pair<int, int>> &es) {
    adj.assign(n + 1, vector<int>());
    for (auto &e : es) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
}

void dfs(int u, vector<bool> &vis, vector<int> &comp) {
    vis[u] = true;
    comp.push_back(u);
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v, vis, comp);
    }
}

vector<int> get_component(int start) {
    vector<bool> vis(n + 1, false);
    vector<int> comp;
    dfs(start, vis, comp);
    return comp;
}

pair<int, int> bfs(int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    int far = start;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[far]) far = v;
            }
        }
    }
    return {far, dist[far]};
}

int tree_diameter() {
    auto p1 = bfs(1);
    auto p2 = bfs(p1.first);
    return p2.second;
}

int main() {
    cin >> n;
    edges.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
    }
    int ans = INT_MAX;
    for (int i = 0; i < n - 1; ++i) {
        vector<pair<int, int>> tmp_edges;
        for (int j = 0; j < n - 1; ++j) {
            if (j != i) tmp_edges.push_back(edges[j]);
        }
        build_adj(tmp_edges);
        vector<int> comp1 = get_component(edges[i].first);
        vector<bool> vis(n + 1, false);
        for (int x : comp1) vis[x] = true;
        int other = -1;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j]) {
                other = j;
                break;
            }
        }
        vector<int> comp2 = get_component(other);
        for (int u : comp1) {
            for (int v : comp2) {
                vector<pair<int, int>> new_edges = tmp_edges;
                new_edges.push_back({u, v});
                build_adj(new_edges);
                int d = tree_diameter();
                ans = min(ans, d);
            }
        }
    }
    cout << ans << endl;
    return 0;
}