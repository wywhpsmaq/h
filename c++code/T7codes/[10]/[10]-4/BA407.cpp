#include <bits/stdc++.h>
using namespace std;
long long sum[100001];
int main() {
    int k, n, i, cnt;
    long long tmp = 0, l, r, mid;
    cin >> n >> k;
    for (i = 1; i <= n; i++) {
        cin >> sum[i];
        if (sum[i] > tmp) tmp = sum[i];
        sum[i] += sum[i - 1];
    }
    l = tmp, r = sum[n];
    while (l < r) {
        mid = l + ((r - l) / 2);
        tmp = cnt = 0;
        i = 1;
        while (cnt <= k && i <= n) {
            i = upper_bound(sum + i, sum + n + 1, tmp + mid) - sum;
            tmp = sum[i - 1];
            cnt++;
        }
        if (cnt > k) l = mid + 1;
        else r = mid;
    }
    cout << ((l <= r) ? l : r);
    return 0;
}