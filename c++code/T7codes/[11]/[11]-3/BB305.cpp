#include<bits/stdc++.h>
using namespace std;
vector<int> v, v1;
int a, b;
int dfs(int c, int d) {
    if (c == 0) {
        for (int i = 0; i < v.size(); i++) {
            cout << "  " << v[i];
        }
        cout << '\n';
        return 0;
    }
    for (int i = d; i <= a - c + 1; i++) {
        v.push_back(v1[i]);
        dfs(c - 1, i + 1);
        v.pop_back();
    }
    return 0;
}
int main() {
    cin >> a >> b;
    v1.push_back(0);
    for (int i = 1; i <= a; i++) {
        v1.push_back(i);
    }
    dfs(b, 1);
}