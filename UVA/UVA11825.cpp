//
//  UVA11825.cpp
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

const int MAXN = 17,MAXMSK = 1 << 17;
int n;
vector<int> adj[MAXN];
int msk[MAXN];
int dp[MAXMSK];
int cov[MAXMSK];
int mxmsk;

void calcCov(){
    memset(cov,0, sizeof(cov));
    for(int i = 0;i < mxmsk;i++){
        for(int j = 0; j < n; j++){
            if(i & (1 << j)){
                cov[i] |= msk[j+1];
            }
        }
    }
}

void solve(){
    memset(msk, 0, sizeof(msk));
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < adj[i].size();j++){
            msk[i] |= (1 << adj[i][j]);
        }
    }
    mxmsk = 1 << n;
    calcCov();
    memset(dp, 0, sizeof(dp));
    int res = 0;
    for(int i = 0; i < mxmsk; i++){
        for(int sub = i; sub; sub--,sub &= i){
            int cpl = i - sub;
            if (cov[sub] == mxmsk-1) {
                dp[i] = max(dp[i],dp[cpl]+1);
                res = max(dp[i],res);
            }
        }
    }
    printf("%d\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %d",&n) != EOF && n) {
        printf("Case %d: ",++caseCnt);
        for (int i = 1; i<= n; i++) {
            adj[i].clear();
            adj[i].push_back(i-1);
            int q;
            scanf(" %d",&q);
            for(int j = 1; j<= q; j++){
                int t;
                scanf(" %d",&t);
                adj[i].push_back(t);
            }
        }
        solve();
    }
    
    
    return 0;
}