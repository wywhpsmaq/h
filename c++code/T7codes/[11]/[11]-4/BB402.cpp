#include <bits/stdc++.h>
using namespace std;
vector<int> z;
vector<int> s(4, 0);
int num;
bool dfs(int x) {
    if (x == z.size()) {
        return s[0] == num && s[1] == num && s[2] == num && s[3] == num;
    }
    for (int i = 0; i < 4; ++i) {
        if (s[i] + z[x] > num) continue;
        s[i] += z[x];
        if (dfs(x + 1)) return true;
        s[i] -= z[x];
        if (s[i] == 0) break;
    }
    return false;
}
int main() {
    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        z.resize(m);
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            cin >> z[i];
            sum += z[i];
        }
        if (sum % 4 != 0) {
            cout << "no" << '\n';
            continue;
        }
        num = sum / 4;
        sort(z.rbegin(), z.rend());
        if (z[0] > num) {
            cout << "no" << '\n';
            continue;
        }
        fill(s.begin(), s.end(), 0);
        if (dfs(0)) {
            cout << "yes" << '\n';
        } else {
            cout << "no" << '\n';
        }
    }
    return 0;
}