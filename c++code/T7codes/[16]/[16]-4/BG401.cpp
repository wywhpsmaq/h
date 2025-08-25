#include <bits/stdc++.h>
using namespace std;
long long n, m, tot,dp[10][1<<10][50], s[1<<10], cnt[1<<10];
bool ch(int x, int y){
    if(s[x] & s[y]) return false;
    if(s[x] & (s[y]<<1)) return false;
    if(s[x] & (s[y]>>1)) return false;
    return true;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < (1<<n); i++){
        if(i & (i << 1)) continue;
        s[++tot] = i;
        int ii = i;
        while(ii){
            if(ii & 1) cnt[tot]++;
            ii >>= 1;
        }
    }
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= tot; j++){
            for(int k = static_cast<int>(cnt[j]); k <= m; k++){
                for(int jj = 1; jj <= tot; jj++){
                    if(!ch(j, jj)) continue;
                    dp[i][s[j]][k] += dp[i-1][s[jj]][k-cnt[j]];
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 1; i <= tot; i++) ans += dp[n][s[i]][m];
    cout << ans;
    return 0;
}