#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> p;
vector<int> b;
int ans = 0;
bool ck(int x, int y, int n) {
    for (int i = 0; i < x; i++) {
        if (b[i] == y || abs(b[i] - y) == abs(i - x)) {
            return false;
        }
    }
    return true;
}
void dfs(int x, int n) {
    if (x == n) {
        if (ans < 99) {
            p.push_back(b);
        }
        ans++;
        return;
    }
    for (int y = 0; y < n; y++) {
        if (ck(x, y, n)) {
            b[x] = y;
            dfs(x + 1, n);
        }
    }
    return;
}
int main() {
    int n, nn;
    cin >> n;
    b.resize(8);
    p.reserve(3);
    dfs(0, 8);
    for (int i = 0; i < n; i++) {
        cin >> nn;
        for (int j = 0; j < 8; j++) {
            cout << p[nn - 1][j] + 1;
        }
        cout << endl;
    }
    return 0;
}