//
//  HDU4507.cpp
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
const LL MODER = 1000000007;
LL pp[22];
int bit[22],dig;
struct State{
    LL cnt,sum,sqs,vis;
} dp[22][8][8];

State dfs(int cur,int dsm7,int m7,bool wildcard){
    if(!cur){
        if (dsm7%7 && m7%7) return {1,0,0};
        else return {0,0,0};
    }
    if(wildcard && dp[cur][dsm7][m7].vis) return dp[cur][dsm7][m7];
    State ret = {0,0,0};
    int end = wildcard?9:bit[cur];
    for (int i = 0; i <= end; i++) {
        if(i == 7) continue;
        State tmp;
        LL A = (pp[cur-1]*(LL)i)%MODER;
        LL AA = (pp[cur-1]*(LL)i)%7;//ISSUE IS HERE!不能用膜过MODER的数再膜7，这时候膜的意义已经不是单纯膜个7了！
        if(i < end) tmp = dfs(cur-1,(dsm7+i)%7,(AA+m7)%7,true);
        else tmp = dfs(cur-1,(dsm7+i)%7,(AA+m7)%7,wildcard);
        ret.cnt += tmp.cnt;
        ret.cnt %= MODER;
        ret.sum += ((A*tmp.cnt)%MODER + tmp.sum%MODER)%MODER;
        ret.sum %= MODER;
        ret.sqs += tmp.sqs;
        ret.sqs %= MODER;
        ret.sqs += (((2*A)%MODER)*(tmp.sum%MODER))%MODER;
        ret.sqs %= MODER;
        ret.sqs += (((A*A)%MODER)*tmp.cnt)%MODER;
        ret.sqs %= MODER;
    }
    ret.vis = true;
    if(wildcard) dp[cur][dsm7][m7] = ret;
    return ret;
}

LL query(LL x){
    dig = 0;
    while (x) {
        bit[++dig] = x%10;
        x /= 10;
    }
    State res = dfs(dig,0,0,false);
    return res.sqs;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    pp[0] = 1;
    for (int i = 1; i <= 20; i++) {
        pp[i] = pp[i-1] * 10LL;
    }
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int i = 1; i <= caseCnt; i++) {
        LL a,b;
#ifndef ONLINE_JUDGE
        scanf(" %lld %lld",&a,&b);
        printf("%lld\n",((query(b) - query(a-1))%MODER + MODER)%MODER);
#endif
#ifdef ONLINE_JUDGE
        scanf(" %I64d %I64d",&a,&b);
        printf("%I64d\n",((query(b) - query(a-1))%MODER + MODER)%MODER);
#endif
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
