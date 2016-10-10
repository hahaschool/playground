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

#define REP(i,t) for(LL i = 0;i < t; i++)
#define REP_R(i,t) for(LL i = t-1;i >= 0; i--)
#define REP_1(i,t) for(LL i = 1;i <= t; i++)
#define REP_1R(i,t) for(LL i = t;i >= 1; i--)
#define REP_ST(i,s,t) for(LL i = s;i <= t; i++)
#define REP_STR(i,s,t) for(LL i = s;i >= t; i--)
#define CASE_LOOP LL ___;scanf(" %d",&___);for(LL __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (LL i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) LL name;scanf(" %d",&name);


using namespace std;

typedef long long LL;
typedef long double LD;

const LL SUSPEND = -0x3f3f3f3f3f3f3f3fLL,LOOP = 0x3f3f3f3f3f3f3f3fLL;
#ifdef LOCAL_DEBUG
const LL MAXN = 105;
#endif
#ifndef LOCAL_DEBUG
const LL MAXN = 200005;
#endif


LL N;
bool vis[MAXN];
bool instk[MAXN];
LL seq[MAXN];
LL dp[MAXN];

LL dfs(LL u){
    if(vis[u]) return dp[u];
    vis[u] = true;
    instk[u] = true;
    //fwd
    LL ret = 0;
    LL cur = u;
    if(cur + seq[cur] > N){
        //out of bound
        ret += seq[cur];
        instk[u] = false;
        return dp[u] = ret;
    }else{
        ret += seq[cur];
        cur += seq[cur];
        //rpd
        if(cur - seq[cur] <= 0){
            //out of bound
            ret += seq[cur];
            instk[u] = false;
            return dp[u] = ret;
        }else{
            ret += seq[cur];
            if(cur - seq[cur] == 1){
                instk[u] = false;
                return dp[u] = SUSPEND;
            }else{
                cur -= seq[cur];
                if(instk[cur]){
                    instk[u] = false;
                    return dp[u] = LOOP;
                }
                LL nxt = dfs(cur);
                if(nxt == LOOP || nxt == SUSPEND){
                    instk[u] = false;
                    return dp[u] = nxt;
                }else{
                    ret += nxt;
                    instk[u] = false;
                    return dp[u] = ret;
                }
            }
        }
    }
}

void solve(){
    REP_1(i, N) vis[i] = instk[i] = false;
    for(LL i = 2;i <= N; i++) if(!vis[i]) dfs(i);
    
    REP_1(i, N-1){
        LL cur = 1 + i - seq[1+i];
        LL res = i + seq[1+i];
        //rpd
        if(cur <= 0){
            cout << res << endl;
        }else{
            if(cur == 1) cout << -1 << endl;
            else if(dp[cur] == LOOP || dp[cur] == SUSPEND) cout << -1 << endl;
            else cout << res + dp[cur] << endl;
        }
    }
    
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (cin >> N) {
        for(LL i = 2;i <= N; i++) cin >> seq[i];
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
