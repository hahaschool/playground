//
//  UVA10891.cpp
//  playground
//
//  Created by 張正昊 on 21/2/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
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

using namespace std;

const int MAXN = 105;
int n;
int seq[MAXN];
int sum[MAXN];
int dp[MAXN][MAXN];
int f[MAXN][MAXN],g[MAXN][MAXN];

int getsum(int from,int to){
    return sum[to] - sum[from-1];
}

void solve(){
    memset(dp, 0, sizeof(dp));
    for(int i = n; i >= 1; i--){
        for(int j = i;j <= n; j++){
            int dval = 0;
            dval = min(dval, f[i+1][j]);
            dval = min(dval, g[i][j-1]);
            dp[i][j] = getsum(i,j) - dval;
            f[i][j] = min(f[i+1][j],dp[i][j]);
            g[i][j] = min(g[i][j-1],dp[i][j]);
        }
    }
    printf("%d\n",2*dp[1][n] - getsum(1, n));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    //dp[i,j] = s[i][j] - min{dp[i+1][j],...,dp[j][j],dp[i][j-1],...,dp[i][i],0};
    while (scanf(" %d",&n) != EOF && n) {
        sum[0] = 0;
        for(int i = 1; i<= n; i++){
            scanf(" %d",&seq[i]);
            sum[i] = sum[i-1] + seq[i];
        }
        solve();
    }
    
    return 0;
}