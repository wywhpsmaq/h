#include <bits/stdc++.h>
using namespace std;
vector<double> x, y, s;
bool a(int n,double v) {
    double t = 0;
    for (int i = 0; i < n; i++) {
        t = max(x[i], t + s[i] / v);
        if (t > y[i]) return false;
    }
    return true;
}
int main(){
    int n;
    cin >> n;
    x.resize(n);
    y.resize(n);
    s.resize(n);
    for (int i = 0; i < n; i++){
        cin >> x[i] >> y[i] >> s[i];
    }
    double r = 1e-9, l = 1;
    while(!a(n,l)) { l *= 2; }
    while(l - r > 1e-3){
        double mid = (r + l) / 2;
        if(a(n,mid)) l = mid;
        else r = mid;
    }
    printf("%.2lf", l);
    return 0;
}