#include <bits/stdc++.h>
using namespace std;
int ksd(){
    //快速读入
    int x = 0, f = 1;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9'){
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar_unlocked();
    }
    return x * f;
}
int main(){
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++){
        v[i] = ksd();
    }
    nth_element(v.begin(), v.begin() + k, v.end());
    cout << v[k];
    return 0;
}