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

#ifdef LOCAL_DEBUG
const int MAXN = 105;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 400005;
#endif

#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)
LL segTree_val[MAXN*4],segTree_siz[MAXN*4],segLazy_mul_siz[MAXN*4];
LL siz[MAXN];
int n;
void segTree_clear(int x){
    segTree_val[x] = segTree_siz[x] = 0;
    segLazy_mul_siz[x] = -1;
}
void segTree_maintain(int x){
    segTree_val[x] = summod(segTree_val[LCH(x)],segTree_val[RCH(x)]);
    segTree_siz[x] = mulmod(segTree_siz[LCH(x)],segTree_siz[RCH(x)]);
}
void segTree_build(int cl = -1,int cr = -1,int x = -1){
    if(x == -1){segTree_build(1,n,1);return;}
    segTree_clear(x);
    if(cl == cr){
        segTree_siz[x] = 1;
        return;
    }else if(cl < cr){
        int mid = (cl + cr) >> 1;
        segTree_build(cl,mid,LCH(x));
        segTree_build(mid+1,cr,RCH(x));
        segTree_maintain(x);
    }
}

void segTree_pushdown(int x){
    if(segLazy_mul_siz[x] != -1){
        segTree_siz[LCH(x)] = mulmod(segTree_siz[LCH(x)], segLazy_mul_siz[x]);
        segTree_val[LCH(x)] = mulmod(segTree_val[LCH(x)], segLazy_mul_siz[x]);
        segTree_siz[RCH(x)] = mulmod(segTree_siz[RCH(x)], segLazy_mul_siz[x]);
        segTree_val[RCH(x)] = mulmod(segTree_val[RCH(x)], segLazy_mul_siz[x]);
        if(segLazy_mul_siz[LCH(x)] == -1) segLazy_mul_siz[LCH(x)] = 1;
        segLazy_mul_siz[LCH(x)] = mulmod(segLazy_mul_siz[LCH(x)], segLazy_mul_siz[x]);
        if(segLazy_mul_siz[RCH(x)] == -1) segLazy_mul_siz[RCH(x)] = 1;
        segLazy_mul_siz[RCH(x)] = mulmod(segLazy_mul_siz[RCH(x)], segLazy_mul_siz[x]);
        segLazy_mul_siz[x] = -1;
    }
}

void segTree_mul(int l,int r,LL val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_mul(l, r, val, 1, n, 1);
        return;
    }
    segTree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_siz[x] = mulmod(segTree_siz[x], val);
        segTree_val[x] = mulmod(segTree_val[x], val);
        if(segLazy_mul_siz[x] == -1) segLazy_mul_siz[x] = 1;
        segLazy_mul_siz[x] = mulmod(segLazy_mul_siz[x], val);
    }else{
        int mid = (cl+cr)>>1;
        segTree_mul(l, r, val, cl, mid, LCH(x));
        segTree_mul(l, r, val, mid+1, cr, RCH(x));
        segTree_maintain(x);
    }
}

void segTree_update_val(int pos,LL val, int cl = -1, int cr = -1,int x = -1){
    if(x == -1){
        segTree_update_val(pos,val,1,n,1);
        return;
    }
    segTree_pushdown(x);
    if(cr < pos || cl > pos) return;
    if(cl >= pos && cr <= pos){
        segTree_val[x] = val*segTree_siz[x];
        return;
    }else{
        int mid = (cl+cr)>>1;
        segTree_update_val(pos, val, cl, mid, LCH(x));
        segTree_update_val(pos, val, mid+1, cr, RCH(x));
        segTree_maintain(x);
    }
}

LL qres;
LL segTree_query_siz(int pos,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        qres = 0;
        segTree_query_siz(pos, 1,n,1);
        return qres;
    }
    segTree_pushdown(x);
    if(cr < pos || cl > pos) return 0;
    if(cl >= pos && cr <= pos){
        qres += segTree_siz[x];
    }else{
        int mid = (cl + cr ) >> 1;
        segTree_query_siz(pos,cl,mid,LCH(x));
        segTree_query_siz(pos,mid+1,cr,RCH(x));
        segTree_maintain(x);
    }
    return 0;
}
LL segTree_query_val(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        qres = 0;
        segTree_query_val(l,r,1,n,1);
        return qres;
    }
    segTree_pushdown(x);
    if(cr < l || cl > r) return 0;
    if(cl >= l && cr <= r){
        qres += segTree_val[x];
    }else{
        int mid = (cl + cr) >> 1;
        segTree_query_val(l, r, cl ,mid ,LCH(x));
        segTree_query_val(l, r, mid+1, cr, RCH(x));
        segTree_maintain(x);
    }
    return 0;
}

int head[MAXN],nxt[MAXN],ed[MAXN],q;
void gph_clr(){
    REP_1(i, n) head[i] = 0;
    q = 2;
}
void gph_ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}


struct Query{
    int typ,arg1,arg2,pid;
} qry[MAXN];
LL V[MAXN],Q;
void buildtree(){
    gph_clr();
    REP_1(i,Q){
        if(qry[i].typ == 1){
            gph_ade(qry[i].arg1,qry[i].pid);
        }
    }
}

int dfs_clock,dfn_in[MAXN],dfn_out[MAXN],par[MAXN];
void dfs(int u,int p){
    ++dfs_clock;
    par[u] = p;
    dfn_in[u] = dfs_clock;
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p){
            dfs(v,u);
        }
    }
    dfn_out[u] = dfs_clock;
}
void getdfn(){
    dfs_clock = 0;
    dfs(1,-1);
}


void solve(){
    buildtree();
    getdfn();
    segTree_build();
    siz[1] = 1;
    segTree_update_val(dfn_in[1], V[1]);
    
    REP_1(i,Q){
        /*
        REP_1(i, n){
            cerr << segTree_query_val(dfn_in[i], dfn_in[i]) << ' ';
        }cerr << endl;
        */
         if(qry[i].typ == 1){
            siz[qry[i].pid] = 1;
            segTree_update_val(dfn_in[qry[i].pid], qry[i].arg2);
            segTree_mul(dfn_in[qry[i].arg1], dfn_out[qry[i].arg1], invmod(siz[qry[i].arg1]));
            siz[qry[i].arg1]++;
            segTree_mul(dfn_in[qry[i].arg1], dfn_out[qry[i].arg1], siz[qry[i].arg1]);
        }else{
            LL res = segTree_query_val(dfn_in[qry[i].arg1], dfn_out[qry[i].arg1]);
            if(par[qry[i].arg1] != -1){
                res = mulmod(res, invmod(segTree_query_siz(dfn_in[par[qry[i].arg1]])));
            }
            cout << res << endl;
        }
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while(cin >> V[1] >> Q){
        n = 1;
        REP_1(i, Q){
            cin >> qry[i].typ >> qry[i].arg1;
            if(qry[i].typ == 1){
                qry[i].pid = ++n;
                cin >> qry[i].arg2;
                V[qry[i].pid] = qry[i].arg2;
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
