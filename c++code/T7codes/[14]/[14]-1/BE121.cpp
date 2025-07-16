#include<bits/stdc++.h>
using namespace std;
int main() {
    int a;
    cin >> a;
    int p[114514];
    for (int i = 0; i < a; i++) {
        cin >> p[i];
    }
    sort(p, p + a);
    int ans = 0, num = (p[0] ^ p[1]);
    for (int i = 2; i < a; i++) {
        if (num ^ p[i] < num) {
            num ^= p[i];
        } else {
            ans += num;
            num = p[i] ^ p[i + 1];
            i += 2;
        }
    }
    cout << ans;
}