#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<int> p[114514];
int ans = 0;
void bfs(int a, int num, int f) {
    ans = max(ans, num);
    for (int i : p[a]) {
        if (i != a) {
            bfs(i, num + 1, a);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        p[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        ans = 0;
        bfs(i, 1, 0);
        cout << ans << '\n';
    }
}