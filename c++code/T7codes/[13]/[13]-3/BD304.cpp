#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;
vector<int> win[MAXN], lose[MAXN];
int N, M;

int bfs(int start, vector<int> graph[]) {
    vector<bool> vis(N + 1, false);
    queue<int> q;
    q.push(start);
    vis[start] = true;
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                cnt++;
            }
        }
    }
    return cnt;
}
int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        win[a].push_back(b);
        lose[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        int win_cnt = bfs(i, win);
        int lose_cnt = bfs(i, lose);
        if (win_cnt + lose_cnt == N - 1) ans++;
    }
    cout << ans << endl;
    return 0;
}