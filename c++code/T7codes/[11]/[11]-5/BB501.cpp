#include <bits/stdc++.h>
using namespace std;
int n;
int p[999][999];
bool v[999][999];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> p[i][j];
        }
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        if (p[i][0] == 0) {
            q.push({i, 0});
            v[i][0] = true;
        }
        if (p[i][n - 1] == 0) {
            q.push({i, n - 1});
            v[i][n - 1] = true;
        }
    }
    for (int j = 0; j < n; ++j) {
        if (p[0][j] == 0) {
            q.push({0, j});
            v[0][j] = true;
        }
        if (p[n - 1][j] == 0) {
            q.push({n - 1, j});
            v[n - 1][j] = true;
        }
    }
    while (!q.empty()) {
        pair a = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = a.first + dx[d], ny = a.second + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !v[nx][ny] && p[nx][ny] == 0) {
                v[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[i][j] == 0 && !v[i][j]) p[i][j] = 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << p[i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}