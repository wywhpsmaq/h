#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> v2;
void dfs(int num, int sum, vector<int> &v) {
    if (sum == n) {
        if (v.size() >= 2) {
            v2.push_back(v);
        }
        return;
    }
    for (int i = num; i <= min(n - 1, n - sum); i++) {
        v.push_back(i);
        dfs(i, sum + i, v);
        v.pop_back();
    }
}

int main() {
    cin >> n;
    vector<int> v;
    dfs(1, 0, v);
    sort(v2.begin(), v2.end());
    for (auto &sol : v2) {
        stringstream ss;
        ss << n << "=";
        for (size_t i = 0; i < sol.size(); i++) {
            ss << sol[i];
            if (i != sol.size() - 1) {
                ss << "+";
            }
        }
        cout << ss.str() << endl;
    }
    return 0;
}