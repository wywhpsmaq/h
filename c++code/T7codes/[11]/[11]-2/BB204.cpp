#include<bits/stdc++.h>
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
        if (ans < 3) {
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
    int n;
    cin >> n;
    b.resize(n);
    p.reserve(3);
    dfs(0, n);
    for (int i = 0; i < min(3, (int)p.size()); i++) {
        for (int j = 0; j < n; j++) {
            cout << p[i][j] + 1;
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }
    cout << ans;
    return 0;
}