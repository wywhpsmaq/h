#include<bits/stdc++.h>
using namespace std;
int main() {
    freopen("U515197-10.in","w",stdout);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> ns(1, 2e3);
    long long n = ns(gen);
    uniform_int_distribution<long long> sm(1, n);
    long long m = sm(gen);
    uniform_int_distribution<long long> sj(INT_MIN, INT_MAX);
    cout << n << " " << m << '\n';
    for (int i = 0;i < n;i++) printf("(%f,%f) ", (double)sj(gen) / 1e5, (double)sj(gen) / 1e5);
}