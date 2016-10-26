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
#endif

#ifdef LOCAL_DEBUG
const int MAXN = 5005;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 5005;
#endif

struct Event{
    int typ,val;//1:INS 2:del
};
vector<Event> bef[MAXN],aft[MAXN];
int A,B,N,K;

LL dp[MAXN][MAXN];

void solve(){
    if(A > B){
        A = N-A+1;
        B = N-B+1;
    }
    /*
    REP_1(i, B){
        bef[i].clear();
        aft[i].clear();
    }
     */
    for(int i = B-2; i >= 1; i--){
        bef[B-1].push_back({1,i});
        aft[i+1].push_back({2,i});
        if(i-1 >= 0) bef[i-1].push_back({1,i});
        if(i-(B-i-1) >= 0) aft[i-(B-i-1)].push_back({2,i});
    }
    //memset(dp, 0, sizeof(dp));
    dp[0][A] = 1;
    REP_1(i, K){
        LL cur = 0;
        REP_1R(j, B-1){
            REP(k, bef[j].size()){
                if(bef[j][k].typ == 1){
                    cur = summod(cur, dp[i-1][bef[j][k].val]);
                }else{
                    cur = summod(cur, -dp[i-1][bef[j][k].val]);
                }
            }
            dp[i][j] = cur;
            REP(k, aft[j].size()){
                if(aft[j][k].typ == 1){
                    cur = summod(cur, dp[i-1][aft[j][k].val]);
                }else{
                    cur = summod(cur, -dp[i-1][aft[j][k].val]);
                }
            }
        }
    }
    LL ans = 0;
    REP_1(i, B) ans = summod(dp[K][i], ans);
    cout << ans << endl;
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d %d %d",&N,&A,&B,&K) != EOF) {
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
