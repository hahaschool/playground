//
//  CF215E.cpp
//  playground
//
//  Created by 張正昊 on 13/8/2016.
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




using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UL;

inline int clz(ULL x){return __builtin_clzll(x);}
inline int lg2(ULL x){return !x?-1:63-clz(x);}

inline ULL getcpy(ULL base,int sig,int len){
    ULL ret = 0;
    REP_1(i, len/sig){
        ret <<= sig;
        ret += base;
    }
    return ret;
}

ULL dp[66];
ULL getpart(ULL x){
    if(x == 1) return 0;
    int k = lg2(x);
    int len = k+1;
    memset(dp, 0, sizeof(dp));
    ULL ret = 0;
    for(int i = 1;i < len; i++){
        if(len%i == 0){
            ULL bas = x >> (len-i);
            if(getcpy(bas, i, len) <= x){
                dp[i]++;
            }
            dp[i] += bas - (1 << (i-1));
            for(int j = 1;j < i; j++){
                if(i%j == 0){
                    dp[i] -= dp[j];
                }
            }
            ret += dp[i];
        }
    }
    return ret;
}

ULL solve(ULL x){
    ULL ret = 0;
    while (x){
        ret += getpart(x);
        x = 1ULL << lg2(x);
        x--;
    }
    return ret;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    ULL l,r;
    cin >> l >> r;
    cout << solve(r) - solve(l-1) << endl;
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
