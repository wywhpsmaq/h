#include<bits/stdc++.h>
using namespace std;
int n, m;
int x, y;
bool v[114514];
int main() {
    cin >> n >> m;
    vector<int> p[11514];
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    vector<int> o;
    cin >> x >> y;
    queue<pair<pair<int, int>, vector<int>>> q;
    o.push_back(x);
    q.push({{x,1},o});
    while (!q.empty()) {
        auto a = q.front();
        if (a.first.first == y) {
            o = a.second;
            break;
        }
        q.pop();
        for (int i : p[a.first.first]) {
            if (!v[i]) {
                v[i] = 1;
                a.second.push_back(i);
                q.push({{i,a.first.second + 1},a.second});
                a.second.pop_back();
            }
        }
    }
}