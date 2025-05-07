#include<bits/stdc++.h>
using namespace std;
int ff(int n, int mod = 10000) {
    int a = 1, b = 1;
    for (int i = 2; i <= n; ++i) {
        int next = (a + b) % mod;
        a = b;
        b = next;
    }
    return a;
}
int main() {

    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        v.push_back(ff(a));
    }
    for (int i : v) {
        cout << i << '\n';
    }
    return 0;
}