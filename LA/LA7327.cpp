//
//  LA7327.cpp
//  playground
//
//  Created by 張正昊 on 4/9/2016.
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
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef long long LL;

const int MAXN = 300005;
const LL MODER = 1000000007;
int n,m;
char buf[MAXN];
LL seq[MAXN];

LL solve(){
    LL sm = 0;
    REP_1(i, n){
        sm *= 10LL;
        sm += seq[i];
        sm %= m;
        if(sm < 0) sm += m;
    }
    if(sm == 0){
        LL a = 0;
        REP_1(i, n){
            sm *= 10LL;
            sm += seq[i];
            sm %= m;
            if(sm == 0) a++;
        }
        LL ret = 1;
        REP(i, a-1){
            ret <<= 1;
            ret %= MODER;
            if(ret < 0) ret += MODER;
        }
        return ret;
    }else return 0;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&n,&m) != EOF) {
        scanf(" %s",buf);
        for(int i = 1;i <= n; i++){
            seq[i] = buf[i-1] - '0';
        }
        printf("%lld\n",solve());
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
