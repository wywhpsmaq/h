#include<bits/stdc++.h>
using namespace std;
int n;
int sum;
vector<int> p;
vector<bool> v;
int c[999][999];
int h[999], l[999];
int dfs(int x, int y) {
    if (y == n) {
        if (l[x] != sum) return 0;
        x += 1, y = 0;
    }
    int sh = 0, sl = 0;
    if (x == n && y == 0) {
        for (int i = 0; i < n; i++) {
            if (h[i] != sum || l[i] != sum) {
                return 0;
            }
            sh += c[i][i];
            sl += c[i][n - i - 1];
        }
        if (sh != sum || sl != sum) return 0;
        cout << sum << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << c[i][j] << " ";
            }
            cout << '\n';
        }
        exit(0);
    }
    for (int i = 0; i < n * n; i++) {
        if (v[i]) continue;
        h[y] += p[i];
        l[x] += p[i];
        v[i] = 1;
        c[x][y] = p[i];
        dfs(x, y + 1);
        v[i] = 0;
        h[y] -= p[i];
        l[x] -= p[i];
    }
    return 0;
}
int main() {
    cin >> n;
    int a;
    for (int i = 0; i < n * n; i++) {
        cin >> a;
        p.push_back(a);
        v.push_back(0);
        sum += a;
    }
    sort(p.begin(), p.end());
    sum /= n;
    dfs(0, 0);
}