//
//  LA4794.cpp
//  playground
//
//  Created by 張正昊 on 22/2/2016.
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

const int MAXN = 20,MAXMSK = 33000,MAXD = 105;
int n;
int x,y;
int seq[MAXN];


int dp[MAXD][MAXMSK];//dp(r,S) c is implicit,r <= c
int area[MAXMSK];
int cnt[MAXMSK];
int mxmsk;

bool dfs(int r,int S){
    if (dp[r][S] != -1) {
        return dp[r][S];
    }
    if (cnt[S] == 1 && area[S] % r == 0) {
        return dp[r][S] = true;
    }
    int c = area[S] / r,nr,nc,cr,cc,S0,Sp;
    for (S0 = S; S0; S0--,S0 &= S) {
        Sp = S - S0;
        for (nr = 1; nr < r; nr++) {
            nc = c;
            if (area[S0] != nr * nc) {
                continue;
            }
            cr = r - nr,cc = c;
            if (dfs(min(nr,nc),S0) && dfs(min(cr,cc), Sp)) {
                return dp[r][S] = true;
            }
        }
        for (nc = 1; nc < c; nc++) {
            nr = r;
            if (area[S0] != nr * nc) {
                continue;
            }
            cr = r,cc = c - nc;
            if (dfs(min(nr,nc), S0) && dfs(min(cr,cc),Sp)) {
                return dp[r][S] = true;
            }
        }
    }
    return dp[r][S] = false;
}

void solve(){
    //Proc MSK
    mxmsk = (1 << n) - 1;
    for(int i = 0; i <= mxmsk; i++){
        area[i] = 0;
        cnt[i] = 0;
        for(int j = 1; j <= n; j++){
            if (i & (1 << (j-1))) {
                area[i] += seq[j];
                cnt[i]++;
            }
        }
    }
    memset(dp, -1, sizeof(dp));
    if (x > y) {
        swap(x, y);
    }
    if (x*y == area[mxmsk] && dfs(x, mxmsk)) {
        puts("Yes");
    }else{
        puts("No");
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d",&n) != EOF && n){
        printf("Case %d: ",++caseCnt);
        scanf(" %d %d",&x,&y);
        for(int i = 1; i<= n; i++){
            scanf(" %d",&seq[i]);
        }
        solve();
    }
    return 0;
}