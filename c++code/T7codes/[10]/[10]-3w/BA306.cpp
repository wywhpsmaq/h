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
    if (p[l] == x) return p[l];
    else return p[l-1];
}
int main() {
    ios::sync_with_stdio(false);
    int a, b, c;
    cin >> a;
    for (int i = 0; i < a; i++)
    {
        cin >> p[i];
    }
    cin >> b;
    for (int i = 0; i < b; i++)
    {
        cin >> c;
        cout << erfen(c,a)<<'\n';
    }
}