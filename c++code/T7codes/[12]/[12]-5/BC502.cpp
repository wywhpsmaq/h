#include<bits/stdc++.h>
using namespace std;
string s, t;
void dfs(int x, int l, int r) {
    if (l > r) return;
    int o = s.find(t[x]);
    dfs(x + 1, l, o - 1);
    dfs(x + o + 1 - l, o + 1, r);
    cout << t[x];
}
int main() {
    cin >> s >> t;
    dfs(0, 0, s.size() - 1);
    return 0;
}