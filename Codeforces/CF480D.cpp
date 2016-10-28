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
const int MAXN = 15,MAXS = 1005;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 505,MAXS = 1005;
#endif

int N,S;
struct Item{
    int in,out,w,s,v;
    bool operator < (const Item &b) const{
        if(out != b.out) return out < b.out;
        return in < b.in;
    }
} item[MAXN];

bool isInside(int a,int b){
    //returns a inside b
    if(item[a].in >= item[b].in && item[a].out <= item[b].out) return true;
    return false;
}

int vis[MAXN];
int dp[MAXN][MAXS];
int dm[MAXN*2][MAXS];
int mx[MAXS];
void dfs(int u){
    vis[u] = true;
    dp[u][item[u].w] = item[u].v;
    REP_1(i, N){
        if(i != u && isInside(i, u)){
            if(!vis[i]) dfs(i);
        }
    }
    memset(dm, 0, sizeof(dm));
    
    int cur = 0;
    REP_1(i, N){
        if(i != u && isInside(i, u)){
            if(cur < item[i].in){
                for(int j = cur+1;j <= item[i].in; j++){
                    REP(k, item[u].s+1){
                        dm[j][k] = max(dm[j][k],dm[j-1][k]);
                    }
                }
                cur = item[i].in;
            }
            
            memset(mx, 0, sizeof(mx));
            REP(j, item[u].s+1){
                if(j) mx[j] = max(mx[j],mx[j-1]);
                mx[j] = max(mx[j],dp[i][j]);
                //cout << mx[j] << ' ';
                dm[item[i].out][j] = max(dm[item[i].out][j],dm[item[i].in][j] + mx[j]);
                if(j+item[u].w <= S)
                    dp[u][j+item[u].w] = max(dp[u][j+item[u].w],item[u].v+dm[item[i].out][j]);
            }
           // cout << endl;
        }
    }
}

int res[MAXN*2];

void solve(){
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    item[0] = {0,2*N,0,S,0};
    sort(item+1, item+1+N);
    dfs(0);
    cout << *max_element(dp[0], dp[0]+S+1) << endl;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&N,&S) != EOF) {
        REP_1(i, N) {
            ADHOC_SCANINT(in);
            ADHOC_SCANINT(out);
            ADHOC_SCANINT(w);
            ADHOC_SCANINT(s);
            ADHOC_SCANINT(v);
            item[i] = {in,out,w,s,v};
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
