#include<bits/stdc++.h>
using namespace std;
vector<int> ans;
extern "C" {
    extern vector<int> xs_(int k, int n, int m);
    extern double Interactive_lib_Fh_jyz(vector<int>& v) {
        double num = 0.00;
        int n = v.size();
        for (int i = 0;i < n;i++) {
            num += double(2 * n - 2 * i + 2) / double(n * n + n) * ans[v[i]];
        }
        return num;
    }
}

int main() {
    int k, n, m, x;
    cin >> k >> n >> m;
    for (int i = 0;i < k;i++) {
        cin >> x;
        ans.push_back(x);
    }
    vector<int> xs_sc = xs_(k, n, m);
    for (int i : xs_sc) {
        cout << i << " ";
    }
}