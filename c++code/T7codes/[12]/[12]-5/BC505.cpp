#include<bits/stdc++.h>
using namespace std;
int n;
int zs[114514], rs[114514];
int p[114];
int dfs(int xx) {
    queue<int> q;
    q.push(xx);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (zs[x] != 0) { cout << zs[x] << " "; q.push(zs[x]); }
        if (rs[x] != 0) { cout << rs[x] << " "; q.push(rs[x]); }
    }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cin >> zs[x] >> rs[x];
        p[zs[x]] = 1, p[rs[x]] = 1;
    }
    int xx;
    for (int i = 1; i <= n; i++) {
        if (p[i] != 1) {
            xx = i;
            break;
        }
    }
    cout << xx << " ";
    dfs(xx);
}