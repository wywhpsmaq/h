#include<bits/stdc++.h>
using namespace std;
struct mg {
    int x, y, a;
    mg(int _x, int _y, int _a) : x(_x), y(_y), a(_a) {}
};
int dfs(int r, int c, const vector<string>& v) {
    vector<pair<int, int>> yp = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<vector<bool>> gm(r, vector<bool>(c, false));
    queue<mg> q;
    q.push(mg(0, 0, 1));
    gm[0][0] = true;

    while (!q.empty()) {
        mg b = q.front();
        q.pop();
        if (b.x == r - 1 && b.y == c - 1) {
            return b.a;
        }
        for (const auto& dir : yp) {
            int nx = b.x + dir.first;
            int ny = b.y + dir.second;
            if (nx >= 0 && nx < r && ny >= 0 && ny < c &&
                !gm[nx][ny] && v[nx][ny] == '.') {
                gm[nx][ny] = true;
                q.push(mg(nx, ny, b.a + 1));
            }
        }
    }

    return -1;
}
int main() {
    int r, c;
    cin >> r >> c;

    vector<string> v(r);
    for (int i = 0; i < r; ++i) {
        cin >> v[i];
    }
    cout << dfs(r, c, v) << endl;

    return 0;
}