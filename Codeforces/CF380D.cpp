//
//  CF380D.cpp
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

const int MAXN = 100005;
int seat[MAXN],asig[MAXN];
const LL MODER = 1000000007;

inline LL get_mod(LL a){
    if(a < 0 || a >= MODER) a %= MODER;
    if(a < 0) a += MODER;
    return a;
}

inline LL mul_mod(LL a,LL b){
    return get_mod(get_mod(a) * get_mod(b));
}

inline LL pow_mod(LL a,LL p){
    LL ret = 1;
    while (p) {
        if(p&1) ret = mul_mod(ret, a);
        a = mul_mod(a, a),p >>= 1;
    }
    return ret;
}

inline LL inv_mod(LL a){
    return pow_mod(a, MODER-2);
}

inline LL add_mod(LL a,LL b){
    return get_mod(get_mod(a) + get_mod(b));
}

LL fac[MAXN];
LL inv_fac[MAXN];

void prep(){
    fac[0] = inv_fac[0] = 1;
    REP_1(i, MAXN-1){
        fac[i] = mul_mod(i, fac[i-1]);
        //不预处理逆元可能被卡超时
        inv_fac[i] = mul_mod(inv_mod(i),inv_fac[i-1]);
    }
}

LL C(int n,int r){
    return mul_mod(fac[n], mul_mod(inv_fac[r], inv_fac[n-r]));
}

int n;
int tot;
int valid[MAXN];
LL calc(int fst){
    LL ret = 1;
    int lt = fst,rt = fst,pv = 1;
    for (int j = 1; j <= tot; j++) {
        int i = valid[j];
        if(i == 1) continue;
        if(asig[i] != 0){
            int lsp = 0,rsp = 0;
            int nlt = 0,nrt = 0;
            if(asig[i] >= lt && asig[i] <= rt){
                //illegal situ.
                //不剪枝可能被卡超时
                return 0;
            }else if(asig[i] < lt){
                lsp = lt - asig[i] - 1;
                nlt = asig[i];
            }else{
                rsp = asig[i] - rt - 1;
                nrt = asig[i];
            }
            
            //claim another space
            if(lsp + rsp + 1 < i - pv){
                if(nlt) rsp += i - pv - lsp - 1;
                else lsp += i - pv - rsp - 1;
            }
            
            //test expansion
            if(nlt) nrt = rt + rsp;
            else nlt = lt - lsp;
            if(nlt >= 1 && nrt <= n){
                ret = mul_mod(ret,C(lsp+rsp,lsp));
            }else{
                //illegal expansion
                //不剪枝可能被卡超时
                return 0;
            }
            lt = nlt,rt = nrt;
            pv = i;
        }
    }
    if(lt == 1 && rt == n) return ret;
    else return mul_mod(ret,C(n-(rt-lt+1),lt-1));
}

LL solve(){
    //如果不去掉自由点，会被卡超时
    tot = 0;
    REP_1(i,n) if(asig[i]) valid[++tot] = i;
    
    if(asig[1]) return calc(asig[1]);
    else{
        LL ret = 0;
        for(int i = 1;i <= n; i++) ret = add_mod(calc(i), ret);
        return ret;
    }
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prep();
    scanf(" %d",&n);
    REP_1(i,n){
        scanf(" %d",&seat[i]);
        asig[seat[i]] = i;
    }
    cout << solve() << endl;
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
