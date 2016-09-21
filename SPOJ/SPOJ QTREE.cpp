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

#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)
#define PAR(x) ((x) >> 1)


const int MAXN = 20005;
int head[MAXN],nxt[MAXN*2],ed[MAXN*2],len[MAXN*2],cod[MAXN*2],q;
int n;
void gph_clr(){
    q = 2;
    REP_1(i, n){
        head[i] = 0;
    }
}
void gph_ade(int u,int v,int c,int id){
    ed[q] = v;
    len[q] = c;
    cod[q] = id;
    nxt[q] = head[u];
    head[u] = q++;
}


int segTree[MAXN*4];
void segTree_init(){
    memset(segTree, 0, sizeof(segTree));
}
void segTree_update(int l,int r,int val,int cl = -1,int cr = -1,int cur = -1){
    if(cur == -1) {segTree_update(l, r, val, 1, n, 1);return;}
    
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){segTree[cur] = val;return;}
    int mid = (cl+cr)>>1;
    segTree_update(l, r, val, cl, mid, LCH(cur));
    segTree_update(l, r, val, mid+1,cr, RCH(cur));
    segTree[cur] = max(segTree[LCH(cur)],segTree[RCH(cur)]);
}

const int INF = 0x3f3f3f3f;
int segTree_qres;
void segTree_query(int l,int r,int cl = -1,int cr = -1,int cur = -1){
    if(cur == -1) {segTree_qres = -INF;segTree_query(l,r,1,n,1);return;}
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){segTree_qres = max(segTree_qres,segTree[cur]);return;}
    int mid = (cl+cr) >> 1;
    segTree_query(l, r, cl, mid, LCH(cur));
    segTree_query(l, r, mid+1, cr, RCH(cur));
}

#define HLD
#ifdef HLD

int siz[MAXN],hvc[MAXN],par[MAXN],dep[MAXN];
void dfs_siz(int u,int p){
    par[u] = p;
    siz[u] = 1;
    hvc[u] = -1;
    int mx = 0;
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if(v != p) {
            dep[v] = dep[u]+1;
            dfs_siz(v, u);
            siz[u] += siz[v];
            if(siz[v] > mx) mx = siz[v],hvc[u] = v;
        }
    }
}

int bid[MAXN];
int dfn,in[MAXN],pos[MAXN],top[MAXN];
void dfs_hld(int u,int p){
    in[u] = ++dfn;
    pos[dfn] = u;
    //go heavy child(if not leaf)
    if(hvc[u] != -1){
        top[hvc[u]] = top[u];
        dfs_hld(hvc[u], u);
    }
    //go other child
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if(v != p){
            if(v != hvc[u]){
                top[v] = v;
                dfs_hld(v, u);
            }
            segTree_update(in[v], in[v], len[i]);
            bid[cod[i]] = in[v];
        }
    }
}



void hld(){
    dfn = 0;
    dfs_siz(1, -1);
    top[1] = 1;
    dep[1] = 1;
    dfs_hld(1, -1);
}

void change(int u,int val){
    segTree_update(bid[u], bid[u], val);
}

int query(int u,int v){
    int ret = -INF;
    while (true) {
        if(top[u] != top[v]){
            //注意下句！当top不相等的时候，需要判断top的深度来决定谁往上跳
            if(dep[top[v]] < dep[top[u]]) swap(u, v);
            segTree_query(in[top[v]], in[v]);
            ret = max(ret,segTree_qres);
            v = par[top[v]];
        }else{
            if(dep[v] < dep[u]) swap(u, v);
            segTree_query(in[u]+1, in[v]);
            ret = max(ret,segTree_qres);
            break;
        }
    }
    return ret;
}

#endif

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    CASE_LOOP{
        scanf(" %d",&n);
        gph_clr();
        segTree_init();
        REP_1(i, n-1){
            ADHOC_SCANINT(a);
            ADHOC_SCANINT(b);
            ADHOC_SCANINT(c);
            gph_ade(a, b, c, i);
            gph_ade(b, a, c, i);
        }
        hld();
        static char buf[10];
        while (scanf(" %s",buf) != EOF) {
            if(buf[0] == 'D') break;
            if(buf[0] == 'Q'){
                ADHOC_SCANINT(a);
                ADHOC_SCANINT(b);
                printf("%d\n",query(a, b));
            }
            if(buf[0] == 'C'){
                ADHOC_SCANINT(a);
                ADHOC_SCANINT(b);
                change(a, b);
            }
        }
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
