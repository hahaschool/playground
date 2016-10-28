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
#define REP_R(i,t) for(int i = t-1;i >= 0; i--)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define REP_1R(i,t) for(int i = t;i >= 1; i--)
#define REP_ST(i,s,t) for(int i = s;i <= t; i++)
#define REP_STR(i,s,t) for(int i = s;i >= t; i--)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef long long LL;
typedef long double LD;

#ifdef COMBINATORICS_MOD1E9
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

#ifdef LOCAL_DEBUG
const int MAXN = 105;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 100005;
#endif

int N,L,X,Y;
int A[MAXN];

set<int> st;
void solve(){
    st.clear();
    REP_1(i, N) st.insert(A[i]);
    bool Xdone = false, Ydone = false;
    REP_1(i, N){
        if(!Xdone){
            int Xatl = A[i]-X, Xatr = A[i]+X;
            if(Xatl >= 0 && st.count(Xatl)) Xdone = true;
            if(Xatr <= L && st.count(Xatr)) Xdone = true;
        }
        if(!Ydone){
            int Yatl = A[i]-Y, Yatr = A[i]+Y;
            if(Yatl >= 0 && st.count(Yatl)) Ydone = true;
            if(Yatr <= L && st.count(Yatr)) Ydone = true;
        }
    }
    if(Xdone && Ydone){
        puts("0");
        return;
    }
    REP_1(i, N){
        int atl = A[i]-(X+Y), atr = A[i]+(X+Y);
        if(atl+X <= L && atl >= 0 && st.count(atl)){
            puts("1");
            printf("%d\n",atl+X);
            return;
        }
        if(atr-X >= 0 && atr <= L && st.count(atr)){
            puts("1");
            printf("%d\n",atr-X);
            return;
        }
        
        atl = A[i]-abs(X-Y), atr = A[i]+abs(X-Y);
        if(A[i]+min(X,Y) <= L && atl >= 0 && st.count(atl)){
            puts("1");
            printf("%d\n",A[i]+min(X,Y));
            return;
        }
        if(atr-max(X,Y) >= 0 && atr <= L && st.count(atr)){
            puts("1");
            printf("%d\n",atr-max(X,Y));
            return;
        }

    }
    if(Xdone && !Ydone){
        puts("1");
        printf("%d\n",Y);
    }else if(Ydone && !Xdone){
        puts("1");
        printf("%d\n",X);
    }else{
        puts("2");
        printf("%d %d\n",X,Y);
    }
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while(scanf(" %d %d %d %d",&N,&L,&X,&Y) != EOF){
        REP_1(i, N) scanf(" %d",&A[i]);
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
