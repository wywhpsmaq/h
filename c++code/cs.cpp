#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <climits>
using namespace std;

struct Node {
    int x, y, cost;
    Node(int x, int y, int cost): x(x), y(y), cost(cost) {}
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> maze(n);
    for (int i = 0; i < n; ++i) cin >> maze[i];

    int sx = -1, sy = -1, tx = -1, ty = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (maze[i][j] == 'S') { sx = i; sy = j; }
            if (maze[i][j] == 'T') { tx = i; ty = j; }
        }

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<Node> q;
    q.push(Node(sx, sy, 0));
    dist[sx][sy] = 0;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = cur.x + dx[d], ny = cur.y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (maze[nx][ny] == 'K') continue;
            int add = (maze[nx][ny] == '#') ? 2 : 1;
            int ncost = cur.cost + add;
            if (dist[nx][ny] > ncost) {
                dist[nx][ny] = ncost;
                q.push(Node(nx, ny, ncost));
            }
        }
    }

    int ans = dist[tx][ty];
    cout << (ans == INT_MAX ? -1 : ans) << endl;
    return 0;
}