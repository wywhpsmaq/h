#include <bits/stdc++.h>
using namespace std;
int n, d, s, t, h, s1, t1, h1;
int main() {
    cin >> n >> d;
    cin >> s >> t >> h;
    for (int i = 0; i < n; i++) {
        cin >> s1 >> t1 >> h1;
        if (abs(h - h1) > d) {
            cout << "No\n";
            continue;
        }
        int sum = (t - s) - (t1 - s1);
        if (sum == 0) cout << (s == s1 && t == t1 ? "Always\n" : "No\n");
        else {
            if ((double(s1 - s) / sum) >= 0 && (double(s1 - s) / sum) <= 1) printf("%.12lf\n", s + (t - s) * (double(s1 - s) / sum));
            else cout << "No\n";
        }
    }
}