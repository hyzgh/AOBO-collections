
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;

int n, dp[9][109], a[9], k;

int dfs(int pos, int sum, int limit){
    if(pos==-1) return sum==0;
    if(!limit && dp[pos][sum]!=-1) return dp[pos][sum];
    int ans=0, up=limit?a[pos]:9;
    for(int i=0; i<=up; i++){
        int t1=(sum+i)%k;
        ans+=dfs(pos-1, t1, limit&&(i==a[pos]));
    }
    if(!limit)
        dp[pos][sum%k]=ans;
    return ans;
}

int solve(int n){
    int cnt=0;
    while(n){
        a[cnt++]=n%10;
        n/=10;
    }
    return dfs(cnt-1, 0, 1);
}


int main() {
    // freopen("in", "r", stdin); freopen("out", "w", stdout);
    int T; scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n,&k);
        memset(dp, -1, sizeof dp);
        printf("%d\n", solve(n)-1);
    }
    return 0;
}
