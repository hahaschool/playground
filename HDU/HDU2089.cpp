//
//  HDU2089.cpp
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

int dp[10][10];
int bit[10],dig;
int dfs(int cur,int left,bool wildcard){
    if(!cur) return 1;
    if(wildcard && dp[cur][left] != -1) return dp[cur][left];
    
    int ret = 0;
    int end = wildcard?9:bit[cur];
    for (int i = 0; i <= end; i++) {
        if(i == 4) continue;
        if(left == 6 && i == 2) continue;
        if(i == end) ret += dfs(cur-1, end, wildcard);
        else ret += dfs(cur-1,i,true);
    }
    if(wildcard) dp[cur][left] = ret;
    return ret;
}
int query(int x){
    dig = 0;
    while (x) {
        bit[++dig] = x % 10;
        x /= 10;
    }
    
    return dfs(dig, -1, false);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    memset(dp, -1, sizeof(dp));
    int a,b;
    while (scanf(" %d %d",&a,&b) != EOF && a+b) {
        printf("%d\n",query(b) - query(a-1));
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
