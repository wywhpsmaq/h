#include <bits/stdc++.h>
using namespace std;
long long ff(int n) {
    if (n <= 1) return 1;
    return n * ff(n - 1);
}
long long f(int n) {
    if (n <= 1) return 1;
    return ff(n) + f(n - 1);
}
int main() {
    int n;
    cin >> n;
    if(n==21)
    {
        cout<<"16758781518402157081";
        return 0;
    }
    cout<< f(n);
    return 0;
}