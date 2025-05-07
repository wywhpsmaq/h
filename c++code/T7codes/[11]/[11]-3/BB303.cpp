#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
bool f(const vector<int>& v, int num) {
    for (int x : v) {
        if (gcd(x, num) != 1) {
            return false;
        }
    }
    return 1;
}
int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<vector<int>> v;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    for (int num : nums) {
        bool bf = false;
        for (auto& v : v) {
            if (f(v, num)) {
                v.push_back(num);
                bf = 1;
                break;
            }
        }
        if (!bf) {
            v.push_back({num});
        }
    }
    cout << v.size();
    return 0;
}