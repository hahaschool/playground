//
//  CF367E.cpp
//  playground
//
//  Created by 張正昊 on 5/9/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <cmath>
#include <map>
#include <complex>
#include <functional>
#include <numeric>
#include <bitset>

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef long long LL;

int n,m,x;
LL dp[2][333][333];
LL fac[333];
const LL MODER = 1000000007;
void prep(){
    fac[0] = 1;
    REP_1(i, 332){
        fac[i] = fac[i-1] * (LL)i;
        fac[i] %= MODER;
    }
}

LL solve(){
    if(m > n) return 0;
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    REP_1(i, n){
        int tck = i&1;
        if(i != x) dp[tck][0][0] = i < x;
        //问题出现在上面这一句，注意当i==x的时候，dp[tck][0][0]=0，因为必须要放置L
        //当i < x 的时候，允许dp[tck][0][0] 的情况，所以是1
        //当i >= x的时候，不允许dp[tck][0][0]的情况，所以为2
        else dp[tck][0][0] = 0;
        for(int l = 1;l <= min(i,m); l++){
            for(int r = 0;r <= l;r++){
                dp[tck][l][r] = 0;
                if(i == x){
                    dp[tck][l][r] += dp[tck^1][l-1][r]; //Place L
                    if(r) dp[tck][l][r] += dp[tck^1][l-1][r-1]; //Place LR
                }else{
                    dp[tck][l][r] += dp[tck^1][l-1][r]; //Place L
                    if(r) dp[tck][l][r] += dp[tck^1][l][r-1]; //Place R
                    if(r) dp[tck][l][r] += dp[tck^1][l-1][r-1]; //Place LR
                    dp[tck][l][r] += dp[tck^1][l][r]; //AS IS
                }
                dp[tck][l][r] %= MODER;
                if(dp[tck][l][r] < 0) dp[tck][l][r] += MODER;
            }
        }
    }
    dp[n&1][m][m] *= fac[m];
    dp[n&1][m][m] %= MODER;
    if(dp[n&1][m][m] < 0) dp[n&1][m][m] += MODER;
    return dp[n&1][m][m];
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    prep();
    while(cin >> m >> n >> x){
        cout << solve() << endl;
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
