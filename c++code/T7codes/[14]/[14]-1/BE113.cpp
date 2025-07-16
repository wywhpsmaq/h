#include<bits/stdc++.h>
using namespace std;
int ans = 0, num = 0;
template<typename T>
inline T read() {
    T x = 0;
    char ch = getchar();
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n = read<int>();
    vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(read<int>());
    }
    while (1) {
        bool f = 0, ff = 0;
        for (int i = num; i < v.size(); i++) {
            if (v[i] != 0) {
                v[i]--;
                f = 1;
            } else {
                if (f) ff = 1;
                else num = i;
            }
            if (ff) break;
        }
        if (!f) {
            cout << ans;
            return 0;
        }
        ans++;
    }
}