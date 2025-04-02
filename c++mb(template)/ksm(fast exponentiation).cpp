//快速幂,求a^b%m
#include <bits/stdc++.h>
typedef long long ll;

ll fast_pow(ll a, ll b, ll m) {
    ll result = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) {  // 如果b的当前位为1
            result = (result * a) % m;
        }
        a = (a * a) % m;  // 平方
        b >>= 1;  // b右移一位
    }
    return result;
}
// 使用示例
int main() {
    ll a,b,m;
    scanf("%lld%lld%lld",&a,&b,&m);
    printf("%lld\n",fast_pow(a,b,m));
    return 0;
}