#include <bits/stdc++.h>
using namespace std;
vector<int> s;
vector<bool> v;
int n;
bool dfs(int x, int len, int sum, int r) {
    if (x == 0) return true;
    if (sum == len) {
        return dfs(x - 1, len, 0, 0);
    }
    int p = -1;
    for (int i = r; i < n; i++) {
        if (!v[i] && sum + s[i] <= len && s[i] != p) {
            v[i] = true;
            if (dfs(x, len, sum + s[i], i + 1)) {
                return true;
            }
            v[i] = false;
            p = s[i];
            if (sum == 0) {
                return false;
            }
        }
    }
    return false;
}
int main() {
    cin >> n;
    s.resize(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        sum += s[i];
    }
    sort(s.rbegin(), s.rend());
    v.resize(n, false);
    for (int i = s[0]; i <= sum; i++) {
        if (sum % i != 0) continue;
        if (i < s[0]) continue;
        int x = sum / i;
        fill(v.begin(), v.end(), false);
        if (dfs(x, i, 0, 0)) {
            cout << i;
            return 0;
        }
    }
    cout << sum;
    return 0;
}