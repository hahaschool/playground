//
//  CF666C.cpp
//  playground
//
//  Created by 張正昊 on 26/8/2016.
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

using namespace std;

typedef long long LL;

int n;
string cur;

const int MAXN = 100005, MODER = 1000000007;
LL fac[MAXN],fac_inv[MAXN];
LL fac26[MAXN],fac25[MAXN];
LL fac26_inv[MAXN],fac25_inv[MAXN];
LL get_mod(LL a){
    if(a >= MODER || a < 0) a %= MODER;
    if(a < 0) a += MODER;
    return a;
}

LL mul_mod(LL a,LL b){
    return get_mod(get_mod(a)*get_mod(b));
}

LL pow_mod(LL a,LL p){
    LL ret = 1;
    while (p) {
        if(p&1) ret = mul_mod(ret, a);
        a = mul_mod(a, a);
        p >>= 1;
    }
    return ret;
}

LL sum_mod(LL a,LL b){
    return get_mod(get_mod(a) + get_mod(b));
}

LL inv_mod(LL a){
    return pow_mod(a, MODER-2);
}

void prep(){
    fac[0] = fac_inv[0] = fac26[0] = fac25[0] = fac26_inv[0] = fac25_inv[0] =  1;
    REP_1(i, MAXN-1){
        fac[i] = mul_mod(fac[i-1], i);
        fac_inv[i] = mul_mod(fac_inv[i-1], inv_mod(i));
        fac26[i] = mul_mod(fac26[i-1], 26);
        fac25[i] = mul_mod(fac25[i-1], 25);
        fac26_inv[i] = mul_mod(fac26_inv[i-1], inv_mod(26));
        fac25_inv[i] = mul_mod(fac25_inv[i-1], inv_mod(25));
    }
}

LL C(LL n,LL r){
    return mul_mod(fac[n], mul_mod(fac_inv[r], fac_inv[n-r]));
}

struct Query{
    int id,len,qrn;
    LL res;
} query[MAXN];

bool cmp_qrn(const Query &a,const Query &b){
    if(a.qrn == b.qrn) return a.len < b.len;
    return a.qrn < b.qrn;
}

bool cmp_id(const Query &a,const Query &b){
    return a.id < b.id;
}

int tot = 0;

void solve(){
    sort(query, query+tot, cmp_qrn);
    int cqrn = 0,ccur = 0;
    LL cval = 0;
    REP(i,tot){
        if(query[i].len < query[i].qrn){
            query[i].res = 0;
            continue;
        }
        if(query[i].qrn != cqrn){
            ccur = cqrn = query[i].qrn;
            ccur--;
            cval = 0;
        }
        while(ccur < query[i].len){
            ccur++;
            cval = sum_mod(cval, mul_mod(mul_mod(mul_mod(fac25[ccur], fac25_inv[cqrn]), fac26_inv[ccur]), C(ccur-1,cqrn-1)));
        }
        query[i].res = mul_mod(cval, fac26[query[i].len]);
    }
    
    sort(query, query+tot, cmp_id);
    REP(i, tot){
        cout << query[i].res << endl;
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    prep();
    
    cin >> n >> cur;
    REP_1(i, n){
        ADHOC_CIN(int, op);
        if(op == 1){
            cin >> cur;
        }else{
            ADHOC_CIN(int, a);
            query[tot] = {tot++,a,(int)cur.size(),0};
        }
    }
    solve();
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
