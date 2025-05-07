#include <bits/stdc++.h>
using namespace std;
int main() {
    int p;
    cin >> p;
    vector<long long> m(p);
    for(int i = 0; i < p; i++) {
        cin >> m[i];
    }
    int n = m.size();
    sort(m.begin(), m.end());
    long long o = 1;
    for(int i = 0; i < n; i++) {
        o = (o * (m[i] - i)) % 1000000007;
    }
    cout<<o;
    return 0;
}