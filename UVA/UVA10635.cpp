//
//  UVA10635.cpp
//  playground
//
//  Created by 張正昊 on 20/2/2016.
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

const int MAXN = 255*255;
int n,p,q;
int sqa[MAXN],sqb[MAXN];
int mkr[MAXN];

int dp[MAXN];

int binsearch(int from,int to,int tar){
    int l = from,r = to+1,mid;
    while(l + 1 < r){
        mid = l + (r-l)/2;
        if(dp[mid] <= tar){
            l = mid + 1;
        }else{
            r = mid;
        }
    }
    if (dp[l] <= tar) {
        return r;
    }
    return l;
}

int lis(){
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = sqb[1];
    int len = 1;
    for(int i = 2;i <= q; i++){
        int pos = binsearch(1, len, sqb[i]);
        len = max(len,pos);
        dp[pos] = min(dp[pos],sqb[i]);
    }
    return len;
}

void solve(){
    //remark
    memset(mkr, 0, sizeof(mkr));
    for(int i = 1; i <= p; i++){
        mkr[sqa[i]] = i;
        sqa[i] = i;
    }
    for(int i = 1; i <= q; i++){
        sqb[i] = mkr[sqb[i]];
    }
    printf("%d\n",lis());
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt; d++){
        printf("Case %d: ",d);
        scanf(" %d %d %d",&n,&p,&q);
        p++,q++;
        for(int i = 1; i <= p; i++){
            scanf(" %d",&sqa[i]);
        }
        for(int i = 1; i<= q; i++){
            scanf(" %d",&sqb[i]);
        }
        solve();
    }
    
    
    return 0;
}