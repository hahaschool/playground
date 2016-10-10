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
#define ADHOC_SCANLLD(name) long long name;scanf(" %lld",&name);
#define ADHOC_SCANI64(name) long long name;scanf(" %I64d",&name);
#define ADHOC_SCANCHR(name) char name;scanf(" %c",&name);

//常数太TM大了，没办法过印度OJ
//LCT保平安

using namespace std;

typedef long long LL;
typedef long double LD;

#pragma mark GPH
#ifdef LOCAL_DEBUG
const int MAXN = 400005;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 200005;
#endif
int head[MAXN],ed[MAXN*4],nxt[MAXN*4],q;
int n;
void gph_clr(){
    REP_1(i, n) head[i] = 0;
    q = 2;
}
void ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}


#pragma mark HLD
int dfs_clock;
int dfn[MAXN],top[MAXN],idx[MAXN],lst[MAXN],siz[MAXN],par[MAXN],hvc[MAXN],dep[MAXN];
void hld_prep(int u,int p,int d){
    par[u] = p;
    siz[u] = 1;
    hvc[u] = -1;
    dep[u] = d;
    int mxs = -1;
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p){
            hld_prep(v, u, d+1);
            siz[u] += siz[v];
            if(siz[v] > mxs){
                mxs = siz[v];
                hvc[u] = v;
            }
        }
    }
}

void hld_main(int u,int p){
    ++dfs_clock;
    dfn[u] = dfs_clock;
    idx[dfs_clock] = u;
    if(hvc[u] != -1){
        top[hvc[u]] = top[u];
        lst[hvc[u]] = hvc[u];
        hld_main(hvc[u],u);
        lst[u] = lst[hvc[u]];
    }
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p && v != hvc[u]){
            top[v] = v;
            lst[v] = v;
            hld_main(v, u);
        }
    }
}

void hld(){
    hld_prep(1, -1, 1);
    dfs_clock = 0;
    top[1] = lst[1] = 1;
    hld_main(1, -1);
}


#pragma mark SEG
#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)
#define PAR(x) ((x) >> 1)
const int NONE = -0x3f3f3f3f;
LL segTree_gw[MAXN*4],segTree_brt[MAXN*4],segTree_siz[MAXN*4],segTree_w[MAXN*4];
LL segLazy_w[MAXN*4];
void segTree_pushdown(int cl,int cr,int x){
    if(segLazy_w[x] != NONE){
        int mid = (cl+cr)>>1;
        int lsz = mid-cl+1;
        int rsz = cr-(mid+1)+1;
        segTree_w[LCH(x)] = segLazy_w[x] * lsz;
        segTree_w[RCH(x)] = segLazy_w[x] * rsz;
        segTree_gw[LCH(x)] = segLazy_w[x] * segTree_siz[LCH(x)];
        segTree_gw[RCH(x)] = segLazy_w[x] * segTree_siz[RCH(x)];
        segLazy_w[LCH(x)] = segLazy_w[RCH(x)] = segLazy_w[x];
        segLazy_w[x] = NONE;
    }
}
void segTree_maintain(int x){
    segTree_gw[x] = segTree_gw[LCH(x)] + segTree_gw[RCH(x)];
    segTree_w[x] = segTree_w[LCH(x)] + segTree_w[RCH(x)];
    segTree_brt[x] = segTree_brt[LCH(x)] + segTree_brt[RCH(x)];
}
void segTree_update_w(int l,int r,LL val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        if(l<=r) segTree_update_w(l,r,val,1,n,1);
        return;
    }
    segTree_pushdown(cl,cr,x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_gw[x] = segTree_siz[x]*val;
        segTree_w[x] = val*(LL)(cr-cl+1);
        segLazy_w[x] = val;
        return;
    }
    int mid = (cl+cr)>>1;
    segTree_update_w(l, r, val, cl, mid, LCH(x));
    segTree_update_w(l, r, val, mid+1, cr ,RCH(x));
    segTree_maintain(x);
}
void segTree_update_brt(int pos,LL val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_update_brt(pos, val, 1, n, 1);
        return;
    }
    if(cr < pos || cl > pos) return;
    if(cl >= pos && cr <= pos){
        segTree_brt[x] = val;
        return;
    }
    int mid = (cl+cr) >> 1;
    segTree_update_brt(pos, val, cl, mid, LCH(x));
    segTree_update_brt(pos, val, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

LL segTree_qres;
void segTree_query_gw(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_qres = 0;
        segTree_query_gw(l,r,1,n,1);
        return;
    }
    segTree_pushdown(cl, cr, x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_qres += segTree_gw[x];
        return;
    }
    int mid = (cl+cr)>>1;
    segTree_query_gw(l, r, cl, mid, LCH(x));
    segTree_query_gw(l, r, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

void segTree_query_w(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_qres = 0;
        segTree_query_w(l,r,1,n,1);
        return;
    }
    segTree_pushdown(cl, cr, x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_qres += segTree_w[x];
        return;
    }
    int mid = (cl+cr)>>1;
    segTree_query_w(l, r, cl, mid, LCH(x));
    segTree_query_w(l, r, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

void segTree_query_brt(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_qres = 0;
        segTree_query_brt(l,r,1,n,1);
        return;
    }
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_qres += segTree_brt[x];
        return;
    }
    int mid = (cl+cr)>>1;
    segTree_query_brt(l, r, cl, mid, LCH(x));
    segTree_query_brt(l, r, mid+1, cr, RCH(x));
}

void segTree_erase(int x){
    segTree_w[x] = segTree_gw[x] = segTree_siz[x] = segTree_brt[x] = 0;
    segLazy_w[x] = NONE;
}


LL init_t[MAXN],init_brt[MAXN];
void segTree_build(int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_build(1,n,1);
        return;
    }
    segTree_erase(x);
    if(cl == cr){
        if(idx[cl] != 1){
            segTree_w[x] = 1;
            segTree_siz[x] = siz[idx[cl]];
            segTree_gw[x] = siz[idx[cl]];
        }
        segTree_brt[x] = init_brt[idx[cl]];
        
    }else if(cl < cr){
        int mid = (cl+cr)>>1;
        segTree_build(cl,mid,LCH(x));
        segTree_build(mid+1,cr,RCH(x));
        segTree_maintain(x);
    }
}

#pragma mark MAIN
int N,Q;

void calc_bf(int u,int p){
    segTree_query_w(dfn[u], dfn[u]);
    init_t[u] = siz[u]*segTree_qres;
    init_brt[u] = 0;
    if(hvc[u] != -1){
        calc_bf(hvc[u], u);
        init_t[u] += init_t[hvc[u]];
    }
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p && v != hvc[u]){
            calc_bf(v,u);
            init_t[u] += init_t[v];
            init_brt[u] += init_t[v];
        }
    }
}


void calc_init(int u,int p){
    init_t[u] = siz[u];
    init_brt[u] = 0;
    if(hvc[u] != -1){
        calc_init(hvc[u], u);
        init_t[u] += init_t[hvc[u]];
    }
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p && v != hvc[u]){
            calc_init(v,u);
            init_t[u] += init_t[v];
            init_brt[u] += init_t[v];
        }
    }
}

LL distance(int x){
    LL ret = 0;
    int cur = x;
    while (cur != -1) {
        segTree_query_w(dfn[top[cur]], dfn[cur]);
        ret += segTree_qres;
        cur = par[top[cur]];
    }
    return ret;
}

LL getT(int x){
    LL ret = 0;
    segTree_query_gw(dfn[x], dfn[lst[x]]);
    ret += segTree_qres;
    segTree_query_brt(dfn[x], dfn[lst[x]]);
    ret += segTree_qres;
    return ret;
}

double query(int x){
    double ret = 0;
    ret += getT(x);
    segTree_query_gw(dfn[x], dfn[x]);
    ret -= segTree_qres;
    ret /= (double)siz[x];
    ret += distance(x);
    return ret;
}

bool cmp_dep(const int &a,const int &b){
    return dep[par[a]] > dep[par[b]];
}
vector<int> vec[MAXN];

void tint(int x){
    //PASS1: 0 --> 1
    int cur = x;
    vector<LL> tmvc;
    while(true){
        sort(vec[top[cur]].begin(),vec[top[cur]].end(),cmp_dep);
        for(unsigned long i = 0;i < vec[top[cur]].size(); i++){
            if(dep[par[vec[top[cur]][i]]] <= dep[cur]){
                tmvc.push_back(getT(vec[top[cur]][i]));
            }
        }
        if(par[top[cur]] == -1){
            break;
        }else{
            tmvc.push_back(getT(top[cur]));
            cur = par[top[cur]];
        }
    }
    
    cur = x;
    int tmvcr = 0;
    set<int> st;
    while(true){
        if(lst[cur] != cur){
            //cout << "LIGHT TAIL: " << idx[dfn[cur]+1] << endl;
            segTree_update_w(dfn[cur]+1, dfn[cur]+1, 1);
        }
        vector<int> tmp;
        for(unsigned long i = 0;i < vec[top[cur]].size(); i++){
            if(dep[par[vec[top[cur]][i]]] > dep[cur]){
                tmp.push_back(vec[top[cur]][i]);
            }else{
                segTree_query_brt(dfn[par[vec[top[cur]][i]]], dfn[par[vec[top[cur]][i]]]);
                //cout << "LIGHT UP: " << vec[top[cur]][i] << endl;
                if(st.count(vec[top[cur]][i])){
                    //cout << "SKIPPED!" << endl;
                    
                    tmvcr++;
                    continue;
                }
                st.insert(top[cur]);
                LL brt = segTree_qres;
                brt -= tmvc[tmvcr++];
                segTree_update_w(dfn[vec[top[cur]][i]], dfn[vec[top[cur]][i]], 1);
                brt += getT(vec[top[cur]][i]);
                segTree_update_brt(dfn[par[vec[top[cur]][i]]], brt);
            }
        }
        vec[top[cur]] = tmp;
        
        if(par[top[cur]] == -1){
            break;
        }else{
            segTree_query_brt(dfn[par[top[cur]]], dfn[par[top[cur]]]);
            LL brt = segTree_qres;
            //cout << "BACKING: " << top[cur] << endl;
            st.insert(top[cur]);
            brt -= tmvc[tmvcr++];
            segTree_update_w(dfn[top[cur]], dfn[top[cur]], 1);
            brt += getT(top[cur]);
            segTree_update_brt(dfn[par[top[cur]]], brt);
            cur = par[top[cur]];
        }
    }
    
    /*
     cout << "AFTRE PASS1:" ;
     for(int i = 1;i <= n; i++){
     cout << ' ' <<  getT(i);;
     }cout << endl;
     cout << "BRUTE FORCE:";
     calc_bf(1, -1);
     for(int i = 1;i <= n; i++){
     cout << ' ' <<  init_t[i];;
     }cout << endl;
     cout << "COLOR CONFIGURATION:";
     for(int i = 1;i <= n; i++){
     segTree_query_w(dfn[i], dfn[i]);
     cout << ' ' << segTree_qres;
     }cout << endl;
     */
    //PASS2: 1 --> 0
    cur = x;
    tmvc.clear();
    while (true) {
        if(par[top[cur]] == -1){
            break;
        }else{
            tmvc.push_back(getT(top[cur]));
            cur = par[top[cur]];
        }
    }
    cur = x;
    tmvcr = 0;
    while (true) {
        if(par[top[cur]] == -1){
            segTree_update_w(dfn[top[cur]]+1, dfn[cur], 0);
            //cout << "NULL from " << top[cur] << " to " << cur << endl;
            break;
        }else{
            segTree_query_brt(dfn[par[top[cur]]], dfn[par[top[cur]]]);
            LL brt = segTree_qres;
            brt -= tmvc[tmvcr++];
            segTree_update_w(dfn[top[cur]], dfn[cur], 0);
            //cout << "NULL from " << top[cur] << " to " << cur << endl;
            brt += getT(top[cur]);
            segTree_update_brt(dfn[par[top[cur]]], brt);
            vec[top[par[top[cur]]]].push_back(top[cur]);
            cur = par[top[cur]];
        }
    }
    /*
     cout << "AFTRE PASS2:" ;
     for(int i = 1;i <= n; i++){
     cout << ' ' <<  getT(i);;
     }cout << endl;
     cout << "BRUTE FORCE:";
     calc_bf(1, -1);
     for(int i = 1;i <= n; i++){
     cout << ' ' <<  init_t[i];;
     }cout << endl;
     cout << "COLOR CONFIGURATION:";
     for(int i = 1;i <= n; i++){
     segTree_query_w(dfn[i], dfn[i]);
     cout << ' ' << segTree_qres;
     }cout << endl;
     */
    
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("/Users/hahaschool/Downloads/第一轮集训队作业/MONOPOLY/test20.in", "r", stdin);
    freopen("/Users/hahaschool/Downloads/第一轮集训队作业/MONOPOLY/test20.my", "w", stdout);
    
    clock_t clk = clock();
#endif
    
    CASE_LOOP{
        scanf(" %d",&N);
        n = N;
        REP_1(i, n) if(vec[i].size()) vec[i].clear();
        gph_clr();
        REP_1(i,N-1){
            ADHOC_SCANINT(a);a++;
            ADHOC_SCANINT(b);b++;
            ade(a, b);
            ade(b, a);
        }
        hld();
        calc_init(1, -1);
        segTree_build();
        
        scanf(" %d",&Q);
        int qrycnt = 0;
        REP_1(i, Q){
            ADHOC_SCANCHR(t);
            ADHOC_SCANINT(u);u++;
            if(t == 'O'){
                //cout << "TIN: " << u << endl;
                /*
                 cout << "BEFORE TIN:" ;
                 for(int i = 1;i <= n; i++){
                 
                 cout << ' ' <<  getT(i);;
                 }cout << endl;
                 */
                tint(u);
                /*
                 cout << "AFTRE TIN:" ;
                 for(int i = 1;i <= n; i++){
                 cout << ' ' <<  getT(i);;
                 }cout << endl;
                 cout << "BRUTE FORCE:";
                 calc_bf(1, -1);
                 for(int i = 1;i <= n; i++){
                 cout << ' ' <<  init_t[i];;
                 }cout << endl;
                 */
            }else if(t == 'q'){
                //cout << "No." << ++qrycnt << endl;
                //cout << "QRY: " << u << endl;
                printf("%.10lf\n",query(u));
            }
        }
    }
#ifdef LOCAL_DEBUG
    //puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
