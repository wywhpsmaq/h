#include <bits/stdc++.h>
using namespace std;
int p[999][999] = {0};
int ans = 0;
bool isSafe(int x, int y) {
    for (int i = 0; i < y; i++)
        if (p[x][i]) return false;
    for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
        if (p[i][j]) return false;
    for (int i = x, j = y; i < 8 && j >= 0; i++, j--)
        if (p[i][j]) return false;

    return true;
}
void dds() {
    ans++;
    cout << "No. " << ans << '\n';
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            cout << p[i][j] << " ";
        cout << '\n';
    }
}
bool dfs(int y) {
    if (y >= 8) {
        dds();
        return true;
    }
    bool res = false;
    for (int i = 0; i < 8; i++) {
        if (isSafe(i, y)) {
            p[i][y] = 1;
            res = dfs(y + 1) || res;
            p[i][y] = 0;
        }
    }
    return res;
}
int main() {
    dfs(0);
    return 0;
}