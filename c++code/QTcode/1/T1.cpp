#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    if (n == 1) {
        string ans;
        for (int j = 0; j < m; ++j) {
            ans += (j % 2 == 0) ? 'B' : 'G';
        }
        cout << ans << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            string s;
            if (i % 2 == 0) {
                s = "BGGB";
            } else {
                s = "GBBG";
            }
            string ans;
            for (int j = 0; j < m; ++j) {
                ans += s[j % 4];
            }
            cout << ans << '\n';
        }
    }
    return 0;
}