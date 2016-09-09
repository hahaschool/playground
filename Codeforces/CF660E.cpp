//
//  CF660E.cpp
//  playground
//
//  Created by 張正昊 on 5/9/2016.
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
const int MAXN = 1000005;
const LL MODER = 1000000007;
LL getmod(LL a){
    if(a<0||a>=MODER) a %= MODER;
    if(a<0) a+=MODER;
    return a;
}
LL summod(LL a,LL b){
    return getmod(getmod(a)+getmod(b));
}
LL mulmod(LL a,LL b){
    return getmod(getmod(a)*getmod(b));
}
LL powmod(LL a,LL p){
    LL ret = 1;
    while(p){
        if(p&1) ret = mulmod(ret, a);
        a = mulmod(a, a);
        p >>= 1;
    }
    return ret;
}
LL invmod(LL a){
    return powmod(a, MODER-2);
}

LL n,m;
LL fac[MAXN],facinv[MAXN];
void prep(){
    fac[0] = facinv[0] = 1;
    REP_1(i, MAXN-1){
        fac[i] = mulmod(fac[i-1], i);
        facinv[i] = mulmod(facinv[i-1], invmod(i));
    }
}
LL bin(LL n,LL r){
    return mulmod(mulmod(fac[n], facinv[r]), facinv[n-r]);
}
LL solve(){
    LL ret = 0;
    //Both Formula works.
    //REP_1(i, n) ret = summod(ret, mulmod(powmod(m, i), mulmod(powmod(m-1, n), mulmod(invmod(powmod(m-1, i)), bin(n,i-1)))));
    REP_1(i, n) ret = summod(ret, mulmod(mulmod(powmod(m-1, i-1), mulmod(powmod(m, n),invmod(powmod(m, i-1)))), bin(n,i)));
    ret = summod(ret, powmod(m, n));
    return ret;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    prep();
    while (cin >> n >> m) {
        cout << solve() << endl;
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
