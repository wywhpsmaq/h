#include<bits/stdc++.h>
using namespace std;
int a,b;
vector<int> v;
long long ans=0;
int f(int a,int b,long long num) {
    if(b==0) {
        if(num<=1) return 0;
        if(num==2) {
            ans++;
            return 0;
        }
        for(int i=2; i*i<=num; i++) {
            if(num%i==0) {
                return 0;
            }
        }
        ans++;
        return 0;
    }
    int o=v.size();
    for(int i=a; i<o; i++) {
        int s=v[i];
        v.erase(v.begin()+i);
        f(i,b-1,num+s);
        v.insert(v.begin()+i,s);
    }
    return 0;
}
int main() {
    cin>>a>>b;
    for(int i=0; i<a; i++) {
        int c;
        cin>>c;
        v.push_back(c);
    }
    sort(v.begin(),v.end());
    f(0,b,0);
    cout<<ans;
}