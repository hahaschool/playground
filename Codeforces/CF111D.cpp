//
//  CF111D.cpp
//  playground
//
//  Created by 張正昊 on 7/9/2016.
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

const LL MODER = 1000000007;
LL getmod(LL a){if(a<0||a>=MODER)a%=MODER;if(a<0)a+=MODER;return a;}
LL summod(LL a,LL b){return getmod(getmod(a)+getmod(b));}
LL mulmod(LL a,LL b){return getmod(getmod(a)*getmod(b));}
LL powmod(LL a,LL p){LL ret=1;while(p){if(p&1)ret=mulmod(ret,a);a=mulmod(a,a);p>>=1;}return ret;}
LL invmod(LL a){return powmod(a,MODER-2);}
const int MAXBIN = 1000005;
LL fac[MAXBIN],facinv[MAXBIN];
void prepbin(){fac[0]=facinv[0]=1;REP_1(i,MAXBIN-1){fac[i]=mulmod(fac[i-1],i);facinv[i]=mulmod(facinv[i-1],invmod(i));}}
LL bin(LL n,LL r){return mulmod(mulmod(fac[n],facinv[n-r]),facinv[r]);}



LL n,m,k;
LL dp[1005][1005];
LL f(LL siz,LL clr){
    if(dp[siz][clr] != -1) return dp[siz][clr];
    LL ret = 0;
    REP(i,clr+1){
        //BINOMINAL INVERSED
        ret = summod(ret, mulmod(mulmod(powmod(-1, clr-i), bin(clr, i)), powmod(i, siz)));
    }
    return dp[siz][clr]=ret;
}

void solve(){
    if(m == 1){
        cout << powmod(k, n) << '\n';
        return;
    }
    LL ret = 0;
    REP(i, min(n,k)+1){
        //i is the same color
        for(int j = 0;i + j <= n && i + 2*j <= k; j++){
            LL a = bin(k, i);//Ways to select i colors from k colors
            LL b = mulmod(bin(k-i,j), bin(k-i-j,j));//Ways to select remaining 2j colors
            LL c = powmod(i, n*(m-2));//Ways to fill middle area
            LL d = powmod(f(n,i+j),2);//Ways to fill L/R banner with exactly i+j colors
            ret = summod(ret,mulmod(mulmod(mulmod(a, b), c), d));
        }
    }
    cout << ret << endl;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    prepbin();
    memset(dp, -1, sizeof(dp));
    while (cin >> n >> m >> k) {
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
