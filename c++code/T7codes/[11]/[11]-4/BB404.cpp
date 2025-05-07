#include <bits/stdc++.h>
using namespace std;
int v, g;
int mp = 16;
vector<int> r, b, c, cs;
vector<vector<int>> p;
void dfs(int num) {
    if (c.size() >= mp) return;
    bool f = true;
    for (int i = 0; i < v; i++) {
        if (cs[i] < r[i]) {
            f = false;
            break;
        }
    }
    if (f) {
        if (c.size() < mp || (c.size() == mp && c < b)) {
            mp = c.size();
            b = c;
        }
        return;
    }
    for (int i = num; i < g; i++) {
        c.push_back(i + 1);
        vector<int> sum = cs;
        for (int j = 0; j < v; j++) {
            cs[j] += p[i][j];
        }
        dfs(i + 1);
        cs = sum;
        c.pop_back();
    }
}
int main() {
    cin >> v;
    r.resize(v);
    for (int i = 0; i < v; i++) {
        cin >> r[i];
    }
    cin >> g;
    p.resize(g, vector<int>(v));
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            cin >> p[i][j];
        }
    }
    c.clear();
    cs.assign(v, 0);
    dfs(0);
    cout << mp;
    for (int i : b) {
        cout << " " << i;
    }
    return 0;
}