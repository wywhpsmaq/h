#include<bits/stdc++.h>
using namespace std;
int p[9999];
int n, m;
int ans = 0;
vector<vector<int> >av;
vector<int> num;
int dfs(int x, int a) {
    if (x == n) return 0;
    if (a == m && x != -1) {
        ans++;
        av.push_back(num);
    }
    for (int i = x + 1; i < n; i++) {
        num.push_back(p[i]);
        dfs(i, a + p[i]);
        num.pop_back();
    }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    cin >> m;
    dfs(-1, 0);
    for (int i = 0; i < av.size(); i++) {
        for (int j = 0; j < av[i].size(); j++) {
            cout << av[i][j] << " ";
        }
        cout << '\n';
    }
    cout << av.size();
}