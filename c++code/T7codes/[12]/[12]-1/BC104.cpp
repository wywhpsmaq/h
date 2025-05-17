#include<bits/stdc++.h>
using namespace std;
struct uu{
    vector<int> h;
    vector<int> b;
};
vector<uu> p;
int n;
int main() {
    cin>>n;
    p.resize(n+1);
    for (int i=0;i<n;i++) {
        int a,b,c;
        cin>>a>>b>>c;
        p[a].h.push_back(b);
        p[b].h.push_back(a);
        p[a].b.push_back(c);
        p[b].b.push_back(c);
    }
    queue<pair<int,int>> q;
    q.push({1,0});
    int ans=-1,num=0;
    while (!q.empty()) {
        auto [a,b]=q.front();
        q.pop();
        for (int i=0;i<p[a].h.size();i++) {
            q.push({p[a].h[i],b+p[a].b[i]});
        }
    }
}