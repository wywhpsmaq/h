#include <bits/stdc++.h>
using namespace std;
vector<int> s;
int v[999];
int n;
bool dfs(int x, int len, int sum, int r) {
    if (x == 0) return true;
    if (sum == len) {
        return dfs(x - 1, len, 0, 0);
    }
    int p = -1;
    for (int i = r; i < n; i++) {
        if (!v[i] && sum + s[i] <= len && s[i] != p) {
            v[i] = 1;
            if (dfs(x, len, sum + s[i], i + 1)) {
                return true;
            }
            v[i] = 0;
            p = s[i];
            if (sum == 0) {
                return false;
            }
        }
    }
    return false;
}
int f() {
    sort(s.begin(), s.end());
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += s[i];
    }
    for (int i = s[0]; i <= sum; i++) {
        if (sum % i != 0) continue;
        int x = sum / i;
        fill(v, v + n, 0);
        if (dfs(x, i, 0, 0)) {
            return i;
        }
    }
    return sum;
}
int main() {
    cin >> n;
    s.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    cout << f();
    return 0;
}