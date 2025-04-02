#include<bits/stdc++.h>
using namespace std;
struct no {
    int a, b;
};
bool cmp(no a, no b) {
    return a.a > b.a;
}
bool cpm(no& a, no& b) {
    return a.a < b.a;
}
int main() {
    no p[9999], p1[9999];
    int a, b;
    cin >> a >> b >> p[0].a;
    for (int i = 1; i < a; i++) {
        cin >> p[i].a;
    }
    sort(p, p + a, cpm);
    for (int i = 1; i < a; i++) {
        p[i].b = 0, p1[i - 1].a = p[i].a - p[i - 1].a, p1[i - 1].b = i - 1;
    }
    p1[0].a = -1;
    p[0].b = -1, p[a - 1].b = -1;
    sort(p1, p1 + a, cmp);
    for (int i = 0; i < b - 2; i++) {
        p[p1[i].b].b = -1;
    }
    int x = p[0].a, ans = LLONG_MAX;
    for (int i = 1; i < a; i++) {
        if (p[i].b == -1) {
            ans = min(ans, (p[i].a - x));
            x = p[i].a;
        }
    }
    cout << ans;
}