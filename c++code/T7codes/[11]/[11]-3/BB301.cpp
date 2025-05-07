#include <bits/stdc++.h>
using namespace std;
int a, b;
vector<int> v, v1;
bool vz[9999];
void dfs(int n) {
    if (n == a) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << '\n';
        return;
    }
    for (int i = 1; i <= a; i++) {
        if (!vz[i]) {
            v.push_back(i);
            vz[i] = 1;
            dfs(n + 1);
            vz[i] = 0;
            v.pop_back();
        }
    }
    return;
}
int main() {
    cin >> a;
    dfs(0);
}