//
//  LA7278.cpp
//  playground
//
//  Created by 張正昊 on 12/9/2016.
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
typedef long double LD;

#ifdef USUAL_MOD1E9
const LL MODER = 1000000007;
LL getmod(LL a){if(a<0||a>=MODER)a%=MODER;if(a<0)a+=MODER;return a;}
LL summod(LL a,LL b){return getmod(getmod(a)+getmod(b));}
LL mulmod(LL a,LL b){return getmod(getmod(a)*getmod(b));}
LL powmod(LL a,LL p){LL ret=1;while(p){if(p&1)ret=mulmod(ret,a);a=mulmod(a,a);p>>=1;}return ret;}
LL invmod(LL a){return powmod(a,MODER-2);}
const int MAXBIN = 1005;
LL fac[MAXBIN],facinv[MAXBIN];
void prepbin(){fac[0]=facinv[0]=1;REP_1(i,MAXBIN-1){fac[i]=mulmod(fac[i-1],i);facinv[i]=mulmod(facinv[i-1],invmod(i));}}
LL bin(LL n,LL r){return mulmod(mulmod(fac[n],facinv[n-r]),facinv[r]);}
#endif

const int MAXP = 105,MAXN = 1005;
int P,K;
int siz[MAXP];
int card[MAXP][MAXN];

int sg[MAXP][MAXN];

void dfs(int p,int u){
    //Step1: select k cards,leaving at least one
    static const int CANDSIZ = 33;
    bool cand[CANDSIZ];memset(cand, 0, sizeof(cand));
    for (int k = 0; k <= K && u-k > 0; k++) {
        if(u-k-card[p][u-k]>=0){
            if(sg[p][u-k-card[p][u-k]] == -1)
                dfs(p, u-k-card[p][u-k]);
            cand[sg[p][u-k-card[p][u-k]]] = true;
        }
    }
    REP(i, CANDSIZ){
        if(!cand[i]){
            sg[p][u] = i;
            break;
        }
    }
}

void solve(){
    memset(sg, -1, sizeof(sg));
    int res = 0;
    REP_1(i, P){
        dfs(i, siz[i]);
        res ^= sg[i][siz[i]];
    }
    if(res) puts("Alice can win.");
    else puts("Bob will win.");
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&P,&K) != EOF) {
        REP_1(i, P){
            scanf(" %d",&siz[i]);
            REP_1(j, siz[i]){
                scanf(" %d",&card[i][j]);
            }
        }
        solve();
    }
    
    
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}