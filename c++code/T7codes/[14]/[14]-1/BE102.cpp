#include<bits/stdc++.h>
using namespace std;
int main() {
    string s;
    int k;
    cin >> s >> k;
    s += '0';
    while (k--) {
        for (int i = 1; i < s.size(); i++) {
            if (s[i - 1] > s[i]) {
                s.erase(i - 1, 1);
                break;
            }
        }
    }
    int f = 1;
    s = s.substr(0, s.size() - 1);
    for (auto i : s) {
        if (i != '0') {
            f = 0;
            cout << i;
        } else {
            if (!f) cout << i;
        }
    }
    if (f) cout << "0";
}