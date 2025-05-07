#include<bits/stdc++.h>
using namespace std;
int s[200000];
int main() {
    int n, c;
    cin >> n >> c;
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s, s + n);
    int l = 0, r = 0;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        while (s[l] < s[i] - c && l < n) l++;
        while (s[r] <= s[i] - c && r < n) r++;
        if (s[i] - s[l] == c) sum += r - l;
    }
    cout << sum;
}