//
//  CF295D.cpp
//  playground
//
//  Created by 張正昊 on 8/9/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//Accepted Version
//Enumerate w
//Enumerate upper part (xxxx5)
//preCalculate lower part (4xxx) product times
//This can make in O(n^2) time
//No NTT required

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

#define USUAL_MOD1E9
#ifdef USUAL_MOD1E9
const LL MODER = 1000000007;
LL getmod(LL a){if(a<0||a>=MODER)a%=MODER;if(a<0)a+=MODER;return a;}
LL summod(LL a,LL b){return getmod(getmod(a)+getmod(b));}
LL mulmod(LL a,LL b){return getmod(getmod(a)*getmod(b));}
LL powmod(LL a,LL p){LL ret=1;while(p){if(p&1)ret=mulmod(ret,a);a=mulmod(a,a);p>>=1;}return ret;}
LL invmod(LL a){return powmod(a,MODER-2);}
#endif

const int MAXN = 2005;
int N,M;
int hf[MAXN][MAXN];
void prephf(){
    for(int w = 2;w < MAXN; w++){
        hf[1][w] = 1;
    }
    for(int h = 2;h < MAXN;h++){
        int pfx = 0;
        for(int w = 1;w < MAXN; w++){
            pfx = summod(pfx, hf[h-1][w]);
            hf[h][w] = summod(hf[h][w-1], pfx);
        }
    }
}
int lower[MAXN][MAXN];
void preplower(){
    REP_1(h, MAXN-1){
        int pfx = 0;
        for(int w = 2;w < MAXN; w++){
            pfx = summod(pfx, hf[h][w]);
            lower[h][w] = summod(lower[h][w-1], summod(pfx, hf[h][w]));
        }
    }
}
int sml[MAXN][MAXN];
void prepsml(){
    REP_1(w, MAXN-1){
        int pfx = 0;
        REP_1(h, MAXN-1){
            pfx = summod(pfx,lower[h][w]);
            sml[h][w] = summod(sml[h-1][w], pfx);
        }
    }
}

void prep(){
    prephf();
    preplower();
    prepsml();
}

void solve(){
    int res = 0;
    REP_1(w, M){
        int tim = M+1-w;
        int tmp = 0;
        REP_1(upper, N){
            tmp = summod(tmp, mulmod(hf[upper][w], (N+1-upper)));
            tmp = summod(tmp, mulmod(hf[upper][w], sml[N-upper][w-1]));
        }
        res = summod(res, mulmod(tmp, tim));
    }
    cout << res << endl;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    prep();
    while (cin >> N >> M) {
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
