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

#define COMBINATORICS_MOD1E9
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

const int MAXN = 305,MAXVAL = 100005;
int N,Q,T;
int val[MAXN];
int son[MAXN],par[MAXN];

bool vis[MAXN];
bool havCycle(int u){
    vis[u] = true;
    if(son[u] == -1) return false;
    if(vis[son[u]]) return true;
    return havCycle(son[u]);
}


int equval[MAXN];
LL dp[2][MAXVAL*10];
void solve(){
    bool flg = false;
    REP_1(i, N){
        memset(vis, 0, sizeof(vis));
        if(havCycle(i)){
            flg = true;
            break;
        }
    }
    if(flg){
        puts("0");
        return;
    }
    
    LL t = T;//这个地方TMD会被减爆，然后就RE9了...
    REP_1(i, N) equval[i] = val[i];
    REP_1(i, N){
        if(son[i] != -1 && par[i] == -1){
            int cur = i;
            int curval = 0;
            while(cur != -1){
                curval += val[cur];
                equval[cur] = curval;
                t -= curval;
                cur = son[cur];
            }
        }
    }
    
    REP_1(i, N){
        if(par[i] != -1 && son[i] == -1){
            t += equval[i];
        }
    }
    if(t<0){
        puts("0");
        return;
    }
    memset(dp[0], 0, sizeof(dp[0]));
    dp[0][0] = 1;
    REP_1(i, N){
        REP(j, t+1){
            //DO NOTHIN'
            dp[i%2][j] = getmod(dp[(i-1)%2][j]);
            //INCREMENT
            if(j >= equval[i]) {
                //dp[i][j] = summod(dp[i][j], dp[i-1][j-equval[i]]);
                dp[i%2][j] = summod(dp[i%2][j], dp[i%2][j-equval[i]]);
            }
        }
    }
    cout << dp[N%2][t] << endl;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d %d",&N,&Q,&T) != EOF) {
        REP_1(i, N) son[i] = par[i] = -1;
        REP_1(i, N) scanf(" %d",&val[i]);
        REP_1(i, Q) {
            ADHOC_SCANINT(a);
            ADHOC_SCANINT(b);
            son[a] = b;
            par[b] = a;
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
