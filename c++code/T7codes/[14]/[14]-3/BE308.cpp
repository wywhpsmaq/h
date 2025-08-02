#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x,y});
    }
    sort(v.begin(), v.end(), cmp);
    priority_queue<int> pq; 
    int num = 0;
    for (auto& p : v) {
        int t1 = p.first, t2 = p.second;
        if (num + t1 <= t2) {
            pq.push(t1);
            num += t1;
        }
        else if (!pq.empty() && pq.top() > t1) {
            num -= pq.top() - t1;
            pq.pop();
            pq.push(t1);
        }
    }
    cout << pq.size();
    return 0;
}