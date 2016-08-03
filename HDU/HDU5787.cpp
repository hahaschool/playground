//
//  HDU5787.cpp
//  playground
//
//  Created by 張正昊 on 3/8/2016.
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

using namespace std;

typedef long long LL;
LL L,R;int K;
int fac10[6] = {1,10,100,1000,10000,100000};

inline int appear(int a,int in){
    int ret = 0;
    while (in) {
        if(a == in%10) ret++;
        in /= 10;
    }
    return ret;
}
inline int extend(int orig,int ext){
    if(orig < fac10[K-1]){
        orig *= 10;
        orig += ext;
        orig %= fac10[K];
        if(appear(ext, orig) > 1){
            return -1;
        }
        return orig;
    }else{
        orig *= 10;
        orig += ext;
        orig %= fac10[K];
        if(orig < fac10[K-1]){
            orig += fac10[K];
        }
        if(orig >= fac10[K] && ext == 1){
            if(appear(ext, orig) > 2){
                return -1;
            }
        }else if(appear(ext,orig) > 1){
            return -1;
        }
        return orig;
    }
}

LL wildcard[20][120000];
int dig[20],tot;
LL dfs(int cur,int lst,bool wildcarding){
    if(wildcarding && wildcard[cur][lst] != -1){
        return wildcard[cur][lst];
    }
    if(!cur){
        return 1;
    }
    LL ret = 0;
    int cdr = dig[cur];
    int ed = 0;
    if(wildcarding) ed = 10;
    else ed = cdr;
    
    //wildcard part
    for (int i = 0; i < ed; i++) {
        if(extend(lst, i) != -1) ret += dfs(cur-1, extend(lst, i),true);
    }
    //normal part
    if(!wildcarding && extend(lst, cdr) != -1){
        ret += dfs(cur-1, extend(lst, cdr), false);
    }
    if(wildcarding){
        wildcard[cur][lst] = ret;
    }
    return ret;
}
LL solve(LL a){
    tot = 0;
    memset(wildcard, -1, sizeof(wildcard));
    while (a) {
        dig[++tot] = a%10;
        a /= 10;
    }
    return dfs(tot,0,false);
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while (scanf(" %lld %lld %d",&L,&R,&K) != EOF) {
        printf("%lld\n",solve(R) - solve(L-1));
    }
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
