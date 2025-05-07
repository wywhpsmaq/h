#include <bits/stdc++.h>
using namespace std;
int n, p[999];
int ans = 0;

void dfs(int x, int a) {
    if (a > 25) return;
    if (x == n) {
        if (a == 24) ans++;
        return;
    }
    dfs(x + 1, a + p[x + 1]);
    dfs(x + 1, a - p[x + 1]);
    dfs(x + 1, a * p[x + 1]);
    return;
}
int main() {

}