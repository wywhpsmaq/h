#include<bits/stdc++.h>
using namespace std;
const int ps = 1e6 + 10;
int p[ps];
int erfen(int x, int b) {
    int l = 1, r = b;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (p[mid] >= x) r = mid;
        else l = mid + 1;
    }
    if (p[l] == x) return l;
    else return -1;
}
int main() {
    ios::sync_with_stdio(false);
    int a, b;
    cin >> a;
    for (int i = 0; i < a; i++) {
        cin >> p[i];
    }
    int m = -1;
    cin >> b;
    m = erfen(b, a);
    m++;
    while (p[m] == b) {
        m++;
    }
    cout << m;
}