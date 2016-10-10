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
#define SCANINT(name) scanf(" %d",&name);
#define SCANCHR(name) scanf(" %c",&name);
#define SCANSTR(name) scanf(" %s",name);
#define SCANLLD(name) scanf(" %lld",&name);
#define SCANI64(name) scanf(" %I64d",&name);



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
const int MAXN = 1000005;
#endif

#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)
LL segTree_val[MAXN*4],segTree_siz[MAXN*4],segLazy[MAXN*4];
int n;
void segtree_clear(int x){
    segTree_val[x] = segTree_siz[x] = segLazy[x] = 0;
}
void segtree_maintain(int x){
    segTree_val[x] = segTree_val[LCH(x)] + segTree_val[RCH(x)];
    segTree_siz[x] = segTree_siz[LCH(x)] + segTree_siz[RCH(x)];
}
void segtree_init(int cl = -1,int cr = -1,int x = -1){
    if(x == -1) {segtree_init(1,n,1);return;}
    segtree_clear(x);
    if(cl == cr){
        segTree_siz[x] = 1;
    }else if(cl < cr){
        int mid = (cl+cr)>>1;
        segtree_init(cl,mid,LCH(x));
        segtree_init(mid+1,cr,RCH(x));
        segtree_maintain(x);
    }
}
void segtree_pushdown(int x){
    if(segLazy[x]){
        segTree_val[LCH(x)] = segTree_siz[LCH(x)] - segTree_val[LCH(x)];
        segTree_val[RCH(x)] = segTree_siz[RCH(x)] - segTree_val[RCH(x)];
        segLazy[LCH(x)] ^= 1;
        segLazy[RCH(x)] ^= 1;
        segLazy[x] ^= 1;
    }
}
void segtree_revert(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1) {segtree_revert(l,r,1,n,1);return;}
    segtree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_val[x] = segTree_siz[x] - segTree_val[x];
        segLazy[x] ^= 1;
        return;
    }
    int mid = (cl+cr)>>1;
    segtree_revert(l, r, cl, mid, LCH(x));
    segtree_revert(l, r, mid+1, cr, RCH(x));
    segtree_maintain(x);
}
int qres;
void segtree_query(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){qres = 0;segtree_query(l,r,1,n,1);return;}
    segtree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r) {qres += segTree_val[x];return;}
    int mid = (cl+cr)>>1;
    segtree_query(l,r,cl,mid,LCH(x));
    segtree_query(l,r,mid+1,cr,RCH(x));
    segtree_maintain(x);
}

int N,K;
LL seq[MAXN];
LL A[MAXN],B[MAXN];
struct Event{
    int r,c,l,typ;//typ=1:start typ=2:terminate
    bool operator < (const Event &b) const{
        if(r != b.r) return r < b.r;
        if(typ != b.typ) return typ > b.typ;
        if(c != b.c) return c < b.c;
        return l < b.l;
    }
} evt[MAXN];
int evttot;

LL wins[MAXN];
void solve(){
    evttot = 0;
    sort(seq, seq+N);
    REP(i, K){
        int l = lower_bound(seq, seq+N, A[i]) - seq;
        if(l == N) continue;
        int r = lower_bound(seq, seq+N, B[i]) - seq;
        if(r == N) r--;
        else if(seq[r] > B[i]){
            //边界好烦...这里要多留心
            r--;
            if(r == -1) continue;
        }
        if(l > r) continue;
        l++,r++;
        evt[evttot++] = {l-1,l-1,r-l+1,1};
        evt[evttot++] = {r,l-1,r-l+1,2};
    }
    sort(evt, evt+evttot);
    n = N;
    segtree_init();
    
    for(int u = 0,i = 0; u <= N; u++){
        if(u){
            wins[u] = 0;
            segtree_query(u+1, N);
            wins[u] += qres;
            segtree_query(1, u-1);
            wins[u] += u-1-qres;
        }
        if(evt[i].r == u){
            int j = i;
            while(evt[j].r == u){
                segtree_revert(evt[j].c+1, evt[j].c+evt[j].l);
                j++;
            }
            i = j;
        }
    }
    
    LL res = (LL)N*(N-1LL)*(N-2LL)/6LL;
    REP_1(i, N){
        res -= wins[i]*(wins[i]-1LL)/2LL;
    }
    cout << res << endl;
}


//#define LLD I64
int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&N,&K) != EOF) {
        REP(i, N){
            SCANLLD(seq[i]);
        }
        REP(i, K){
            SCANLLD(A[i]);
            SCANLLD(B[i]);
        }
        solve();
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
