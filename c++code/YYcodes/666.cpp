#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    n *= 2;
    int num;
    for (int i = 3;; i++) {
        if (n % i == 0) {
            num = i;
            break;
        }
    }
    int l = n * 2 / num;
}