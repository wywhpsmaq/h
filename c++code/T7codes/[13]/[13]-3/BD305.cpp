#include<bits/stdc++.h>
using namespace std;
int n, m;
bool qq[114514];
int h[114514], e[114514], w[114514], ne[114514], v[114514], c[114514], idx;
void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
bool f() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
        qq[i] = 1;
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        qq[t] = 0;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (v[j] > v[t] + w[i]) {
                v[j] = v[t] + w[i];
                c[j] = c[t] + 1;
                if (c[j] >= n) return 1;
                if (!qq[j]) {
                    q.push(j);
                    qq[j] = 1;
                }
            }
        }
    }
    return 0;
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    cout << (f() ? "Yes" : "No");
    return 0;
}