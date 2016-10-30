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

typedef unsigned long long LLU;
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
const int MAXN = 200,MAXLOG = 20;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 100005*2,MAXLOG = 20;
#endif

int N,Q;
int head[MAXN],ed[MAXN],nxt[MAXN],q;
void gph_clr(){
    q = 2;
    REP_1(i, N) head[i] = 0;
}
void gph_ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}


int par[MAXN][MAXLOG],dep[MAXN],dfn[MAXN],dfs_clock;
void dfs(int u,int p,int d){
    dfn[u] = ++dfs_clock;
    par[u][0] = p;
    dep[u] = d;
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p){
            dfs(v,u,d+1);
        }
    }
}
void prepare(){
    dfs_clock = 0;
    dfs(1,-1,1);
    REP_1(i, MAXLOG-1){
        REP_1(u, N){
            if(par[u][i-1] != -1) par[u][i] = par[par[u][i-1]][i-1];
            else par[u][i] = -1;
        }
    }
}
int lca(int a,int b){
    if (dep[a] != dep[b]) {
        if(dep[a] < dep[b]) swap(a, b);
        int tar = dep[a] - dep[b];
        REP(i, MAXLOG){
            if(tar & (1<<i)){
                a = par[a][i];
            }
        }
    }
    if(a == b) return a;
    REP_R(i, MAXLOG){
        if(par[a][i] != par[b][i]){
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}


int Qn,Qq[MAXN];
bool cmp_dfn(const int &a,const int &b){
    return dfn[a] < dfn[b];
}


int virt_par[MAXN];
int virt_head[MAXN],virt_nxt[MAXN],virt_ed[MAXN],virt_q;
void virt_ade(int s,int t){
    virt_ed[virt_q] = t;
    virt_nxt[virt_q] = virt_head[s];
    virt_head[s] = virt_q++;
}
set<int> st;
int stk[MAXN*2],top;
int virt_rt,virt_rtdep;
void buildvirt(){
    st.clear();
    virt_q = 2;
    virt_rtdep = 0x3f3f3f3f;
    top = 0;
    REP_1(i, Qn){
        int u = Qq[i];
        virt_head[u] = 0;
        if(dep[u] < virt_rtdep) virt_rt = u,virt_rtdep = dep[u];
        st.insert(u);
        //cout << u << endl;
        if(!top){
            stk[++top] = u;
            virt_par[u] = -1;
        }else{
            int p = lca(u,stk[top]);
            virt_head[p] = 0;
            if(dep[p] < virt_rtdep) virt_rt = p,virt_rtdep = dep[p];
            st.insert(p);
            //cout << p << endl;
            while(dep[stk[top]] > dep[p]){
                if(dep[stk[top-1]] <= dep[p]){
                    virt_par[stk[top]] = p;
                }
                top--;
            }
            if(stk[top] != p){
                //Non-important point p will be instered to tree here
                virt_par[p] = stk[top];
                stk[++top] = p;
            }
            virt_par[u] = p;
            stk[++top] = u;
        }
    }
    
    
    //cout << "virt_rt:" << virt_rt << endl;
    virt_par[virt_rt] = -1;
    for(set<int>::iterator it = st.begin();it != st.end();it++){
        if(virt_par[*it] != -1){
            //cout << "Linking " << *it << " <-> " << virt_par[*it] << endl;
            virt_ade(virt_par[*it], *it);
            virt_ade(*it, virt_par[*it]);
        }
    }
    
}

int dp[MAXN];
int getdp(int u,int p){
    bool resolved = false;
    dp[u] = 0;
    int cnt = 0,sum = 0;
    for(int i = virt_head[u];i;i = virt_nxt[i]){
        int v = virt_ed[i];
        if(v != p){
            cnt += getdp(v,u);
            sum += dp[v];
        }
    }
    if(st.count(u)){
        resolved = false;
        dp[u] = sum+cnt;
    }else{
        if(!cnt){
            resolved = true;
            dp[u] = sum;
        }else if(cnt == 1){
            resolved = false;
            dp[u] = sum;
        }else{
            resolved = true;
            dp[u] = sum+1;
        }
    }
    
    if(!resolved) return 1;
    else return 0;
}

int solve(){
    if(Qn == 1) return 0;
    sort(Qq+1,Qq+1+Qn,cmp_dfn);
    buildvirt();
    
    st.clear();
    REP_1(i, Qn) st.insert(Qq[i]);
    REP_1(i, Qn) if(st.count(par[Qq[i]][0])) return -1;
    
    getdp(virt_rt,-1);
    return dp[virt_rt];
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d",&N) != EOF) {
        gph_clr();
        REP_1(i, N-1){
            ADHOC_SCANINT(a);
            ADHOC_SCANINT(b);
            gph_ade(a,b);
            gph_ade(b,a);
        }
        prepare();
        scanf(" %d",&Q);
        REP_1(i, Q){
            scanf(" %d",&Qn);
            REP_1(j, Qn) scanf(" %d",&Qq[j]);
            cout << solve() << endl;
        }
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
