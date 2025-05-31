#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> db(n + 1, -1), bd(n + 1, 0), rn(n + 1, 0);
    vector<int> d1(n + 1, -1), d2(n + 1, -1);
    vector<int> p1(n + 1, -1), p3;
    vector<bool> o(n + 1, false);
    vector<vector<int>> p(n + 1);
    vector<int> v(n + 1, 0);
    queue<int> q, q1;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        p[a].push_back(b);
        p[b].push_back(a);
        v[i + 1] = c;
    }
    d1[1] = 0;
    q.push(1);
    int a = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (d1[u] > d1[a]) a = u;
        for (int v : p[u]) {
            if (d1[v] == -1) {
                d1[v] = d1[u] + 1;
                q.push(v);
            }
        }
    }
    d2[a] = 0, p1[a] = -1;
    q1.push(a);
    int b = a;
    while (!q1.empty()) {
        int u = q1.front();
        q1.pop();
        if (d2[u] > d2[b]) b = u;
        for (int v : p[u]) {
            if (d2[v] == -1) {
                d2[v] = d2[u] + 1;
                p1[v] = u;
                q1.push(v);
            }
        }
    }
    int ml = d2[b], num = b;
    while (num != -1) {
        p3.push_back(num);
        num = p1[num];
    }
    reverse(p3.begin(), p3.end());
    for (int u : p3) o[u] = true;
    for (int u : p3) {
        db[u] = 0;
        rn[u] = u;
        q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : p[u]) {
            if (db[v] == -1) {
                db[v] = db[u] + 1;
                rn[v] = rn[u];
                if (db[v] > bd[rn[u]]) {
                    bd[rn[u]] = db[v];
                }
                q.push(v);
            }
        }
    }
    int l = 0;
    for (int i = 0; i < p3.size(); i++) {
        if (bd[p3[i]] == i){
            l = i;
        }
        else{
            break;
        }
    }
    int r = p3.size() - 1;
    for (int i = p3.size() - 1; i >= 0; i--) {
        if (bd[p3[i]] == (p3.size() - 1 - i)){
            r = i;
        }
        else{
            break;
        }
    }
    long long ans = 0;
    if (l <= r) {
        for (int i = l; i <= r; i++) {
            ans += v[p3[i]];
        }
    }
    cout << ans;
}