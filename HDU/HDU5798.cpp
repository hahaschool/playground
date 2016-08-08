//
//  HDU5798.cpp
//  playground
//
//  Created by 張正昊 on 8/8/2016.
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

using namespace std;
typedef long long LL;

const int MAXN = 100005;
int N;
int A[MAXN];
LL dp[22][22][2][2];
int b[22];
LL res_isb,res_x;
void dfs(int dig,LL isb,int x){
    if(dig == 20){
        if(isb < res_isb || (isb == res_isb && x < res_x)){
            res_isb = isb;
            res_x = x;
        }
        return;
    }
    b[dig] = 0;
    int sum = 0;
    for(int i = 0;i < dig;i++){
        sum += dp[dig][i][0][b[i]];
    }
    dfs(dig+1, isb + sum, x);
    
    b[dig] = 1;
    sum = 0;
    for(int i = 0;i < dig;i++){
        sum += dp[dig][i][1][b[i]];
    }
    dfs(dig+1, isb + sum, x + (1<<dig));
}

void solve(){
    memset(dp, 0, sizeof(dp));
    LL sum = 0;
    for(int i = 2;i <= N; i++){
        int x = A[i-1],y = A[i];
        if(x > y) swap(x, y);
        int h,diff = x^y;
        for(h = 20;h >= 0; h--)
            if(diff & (1 << h))
                break;
        if(h == -1) continue;
        sum += 1 << h;
        for (int j = h-1; j >= 0; j--) {
            if(!((1 << j) & (x^y))) continue;
            LL t = 1 << j;
            if((1 << j) & x) t = -t;
            dp[h][j][0][0] += t;
            dp[h][j][1][1] += t;
            dp[h][j][1][0] -= t;
            dp[h][j][0][1] -= t;
        }
    }
    
    res_isb = res_x = 1e18;
    dfs(0, 0, 0);
    printf("%lld %lld\n",res_x,res_isb+sum);
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    CASE_LOOP{
        scanf(" %d",&N);
        for(int i = 1;i <= N; i++){
            scanf(" %d",&A[i]);
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
