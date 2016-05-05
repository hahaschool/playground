//
//  HDU3555.cpp
//  playground
//
//  Created by 張正昊 on 5/5/2016.
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

typedef long long LL;

LL dp[22][10][2],wc[22];
int bit[22],dig;
LL dfs(int cur,int left,int fortynine,bool wildcard){
    if(!cur) return fortynine?1:0;
    if(fortynine && wildcard) return wc[cur];
    if(wildcard && dp[cur][left][fortynine] != -1) return dp[cur][left][fortynine];
    LL ret = 0;
    int end = wildcard?9:bit[cur];
    for (int i = 0; i <= end; i++) {
        if (left == 4 && i == 9) ret += dfs(cur-1, i, 1,wildcard);
        else if(i < end) ret += dfs(cur-1, i,fortynine, true);
        else ret += dfs(cur-1, i,fortynine ,wildcard);
    }
    if(wildcard) dp[cur][left][fortynine] = ret;
    return ret;
}

LL query(LL x){
    dig = 0;
    while (x) {
        bit[++dig] = x%10;
        x /= 10;
    }
    return dfs(dig, -1,false,false);
}

int main(){
    memset(dp, -1, sizeof(dp));
    wc[0] = 1;
    for(int i = 1;i <= 20; i++){
        wc[i] = wc[i-1] * 10LL;
    }
    
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int i = 1; i <= caseCnt; i++) {
        LL a;
        scanf(" %I64d",&a);
        printf("%I64d\n",query(a));
    }
    return 0;
}
