#include<bits/stdc++.h>
using namespace std;
int main() {
    double n;
    cin >> n;
    double l = 1.0;
    double r = n;
    const double jd = 1e-8;//精度
    while (r - l > jd) {//二分求解
        double mid = (l + r) / 2;
        double c = mid * mid * mid;
        if (c > n) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.6f", l);
    return 0;
}