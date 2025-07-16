#include<bits/stdc++.h>
using namespace std;
float ma(float a, float b) {
    return (a > b) ? a : b;
}
int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    vector<float> v(n, 0.0), s(n, 0.0);
    v[0] = 100.0;
    s[0] = 100.0 * p[0];
    for (int i = 1; i < n; ++i) {
        v[i] = ma(v[i - 1], s[i - 1] / p[i]);
        s[i] = ma(s[i - 1], v[i - 1] * p[i]);
    }
    printf("%.2f", max(v[n - 1], s[n - 1] / p[n - 1]));
    return 0;
}