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

#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)

#ifdef LOCAL_DEBUG
const int MAXN = 5005;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 200005;
#endif
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
const LL NONE = -INF;
LL segTree_a[MAXN*4],segTree_b[MAXN*4],segTree_ab[MAXN*4];
LL segTree_mina[MAXN*4],segTree_maxa[MAXN*4],segTree_siz[MAXN*4];
LL segTree_minb[MAXN*4],segTree_maxb[MAXN*4];
LL segLazy_a[MAXN*4],segLazy_b[MAXN*4];
LL segDelta_a[MAXN*4],segDelta_b[MAXN*4];
int n;

void segTree_pushdown(int x){
    //set型标签会覆盖delta型标签 注意
    if(segLazy_a[x] != NONE){
        if(segTree_siz[LCH(x)]){
            segTree_a[LCH(x)] = segTree_siz[LCH(x)] * segLazy_a[x];
            segTree_ab[LCH(x)] = segLazy_a[x] * segTree_b[LCH(x)];
            segTree_mina[LCH(x)] = segTree_maxa[LCH(x)] = segLazy_a[x];
            segLazy_a[LCH(x)] = segLazy_a[x];
            segDelta_a[LCH(x)] = 0;
        }
        if(segTree_siz[RCH(x)]){
            segTree_a[RCH(x)] = segTree_siz[RCH(x)] * segLazy_a[x];
            segTree_ab[RCH(x)] = segLazy_a[x] * segTree_b[RCH(x)];
            segTree_mina[RCH(x)] = segTree_maxa[RCH(x)] = segLazy_a[x];
            segLazy_a[RCH(x)] = segLazy_a[x];
            segDelta_a[RCH(x)] = 0;
        }
        segLazy_a[x] = NONE;
    }
    
    if(segLazy_b[x] != NONE){
        if(segTree_siz[LCH(x)]){
            segTree_b[LCH(x)] = segTree_siz[LCH(x)] * segLazy_b[x];
            segTree_ab[LCH(x)] = segLazy_b[x] * segTree_a[LCH(x)];
            segTree_minb[LCH(x)] = segTree_maxb[LCH(x)] = segLazy_b[x];
            segLazy_b[LCH(x)] = segLazy_b[x];
            segDelta_b[LCH(x)] = 0;
        }
        if(segTree_siz[RCH(x)]){
            segTree_b[RCH(x)] = segTree_siz[RCH(x)] * segLazy_b[x];
            segTree_ab[RCH(x)] = segLazy_b[x] * segTree_a[RCH(x)];
            segTree_minb[RCH(x)] = segTree_maxb[RCH(x)] = segLazy_b[x];
            segLazy_b[RCH(x)] = segLazy_b[x];
            segDelta_b[RCH(x)] = 0;
        }
        segLazy_b[x] = NONE;
    }
    
    
    if(segDelta_a[x]){
        if(segTree_siz[LCH(x)]){
            segTree_a[LCH(x)] += segTree_siz[LCH(x)] * segDelta_a[x];
            segTree_ab[LCH(x)] += segDelta_a[x] * segTree_b[LCH(x)];
            segTree_mina[LCH(x)] += segDelta_a[x];
            segTree_maxa[LCH(x)] += segDelta_a[x];
            segDelta_a[LCH(x)] += segDelta_a[x];
           //segLazy_a[LCH(x)] += segDelta_a[x];
        }
        if(segTree_siz[RCH(x)]){
            segTree_a[RCH(x)] += segTree_siz[RCH(x)] * segDelta_a[x];
            segTree_ab[RCH(x)] += segDelta_a[x] * segTree_b[RCH(x)];
            segTree_mina[RCH(x)] += segDelta_a[x];
            segTree_maxa[RCH(x)] += segDelta_a[x];
            segDelta_a[RCH(x)] += segDelta_a[x];
            //segLazy_a[RCH(x)] += segDelta_a[x];
        }
        segDelta_a[x] = 0;
    }
    
    if(segDelta_b[x]){
        if(segTree_siz[LCH(x)]){
            segTree_b[LCH(x)] += segTree_siz[LCH(x)] * segDelta_b[x];
            segTree_ab[LCH(x)] += segDelta_b[x] * segTree_a[LCH(x)];
            segTree_minb[LCH(x)] += segDelta_b[x];
            segTree_maxb[LCH(x)] += segDelta_b[x];
            segDelta_b[LCH(x)] += segDelta_b[x];
            //segLazy_b[LCH(x)] += segDelta_b[x];
        }
        if(segTree_siz[RCH(x)]){
            segTree_b[RCH(x)] += segTree_siz[RCH(x)] * segDelta_b[x];
            segTree_ab[RCH(x)] += segDelta_b[x] * segTree_a[RCH(x)];
            segTree_minb[RCH(x)] += segDelta_b[x];
            segTree_maxb[RCH(x)] += segDelta_b[x];
            segDelta_b[RCH(x)] += segDelta_b[x];
            //segLazy_b[RCH(x)] += segDelta_b[x];
        }
        segDelta_b[x] = 0;
    }
}

LL A,B;
inline bool isAnomaly(int x){
    if(segTree_mina[x] <= 0 || segTree_minb[x] <= 0) return true;
    if(segTree_maxa[x] > A || segTree_maxb[x] > B) return true;
    return false;
}
inline void segTree_erase(int x){
    segTree_a[x] = segTree_b[x] = segTree_ab[x] = 0;
    segTree_mina[x] = segTree_minb[x] = INF;
    segTree_maxa[x] = segTree_maxb[x] = -INF;
    segTree_siz[x] = 0;
    
    segLazy_a[x] = segLazy_b[x] = NONE;
    segDelta_a[x] = segDelta_b[x] = 0;
}

void segTree_maintain(int x){
    segTree_a[x] = segTree_a[LCH(x)] + segTree_a[RCH(x)];
    segTree_b[x] = segTree_b[LCH(x)] + segTree_b[RCH(x)];
    segTree_ab[x] = segTree_ab[LCH(x)] + segTree_ab[RCH(x)];
    segTree_siz[x] = segTree_siz[LCH(x)] + segTree_siz[RCH(x)];
    segTree_maxa[x] = max(segTree_maxa[LCH(x)],segTree_maxa[RCH(x)]);
    segTree_mina[x] = min(segTree_mina[LCH(x)],segTree_mina[RCH(x)]);
    segTree_maxb[x] = max(segTree_maxb[LCH(x)],segTree_maxb[RCH(x)]);
    segTree_minb[x] = min(segTree_minb[LCH(x)],segTree_minb[RCH(x)]);
}

void segTree_anomaly(int cl,int cr,int x){
    segTree_pushdown(x);
    if(cl == cr){
        if(isAnomaly(x)) segTree_erase(x);
    }else if(cl < cr){
        int mid = (cl + cr) >> 1;
        if(segTree_siz[LCH(x)] && isAnomaly(LCH(x))) segTree_anomaly(cl, mid, LCH(x));
        if(segTree_siz[RCH(x)] && isAnomaly(RCH(x))) segTree_anomaly(mid+1, cr, RCH(x));
        segTree_maintain(x);
    }
}

void segTree_update_a(int l,int r,int val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1) {
        segTree_update_a(l, r, val, 1, n, 1);
        if(isAnomaly(1)) segTree_anomaly(1, n, 1);
        return;
    }
    
    segTree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_a[x] = val * segTree_siz[x];
        segTree_ab[x] = val * segTree_b[x];
        segTree_mina[x] = segTree_maxa[x] = val;
        segLazy_a[x] = val;
        return;
    }
    int mid = (cl + cr) >> 1;
    if(segTree_siz[LCH(x)]) segTree_update_a(l, r, val, cl, mid, LCH(x));
    if(segTree_siz[RCH(x)]) segTree_update_a(l, r, val, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

void segTree_update_b(int l,int r,int val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_update_b(l, r, val, 1, n, 1);
        if(isAnomaly(1)) segTree_anomaly(1, n, 1);
        return;
    }
    
    segTree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_b[x] = val * segTree_siz[x];
        segTree_ab[x] = val * segTree_a[x];
        segTree_minb[x] = segTree_maxb[x] = val;
        segLazy_b[x] = val;
        return;
    }
    int mid = (cl + cr) >> 1;
    if(segTree_siz[LCH(x)]) segTree_update_b(l, r, val, cl, mid, LCH(x));
    if(segTree_siz[RCH(x)]) segTree_update_b(l, r, val, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

void segTree_delta_a(int l,int r,int val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_delta_a(l,r,val,1,n,1);
        if(isAnomaly(1)) segTree_anomaly(1, n, 1);
        return;
    }
    
    segTree_pushdown(x);
    if(cr < l || cl > r)return;
    if(cl >= l && cr <= r){
        segTree_a[x] += val * segTree_siz[x];
        segTree_ab[x] += val * segTree_b[x];
        segTree_mina[x] += val;
        segTree_maxa[x] += val;
        segDelta_a[x] += val;
        return;
    }
    int mid = (cl + cr) >> 1;
    if(segTree_siz[LCH(x)]) segTree_delta_a(l, r, val, cl, mid, LCH(x));
    if(segTree_siz[RCH(x)]) segTree_delta_a(l, r, val, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

void segTree_delta_b(int l,int r,int val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_delta_b(l, r, val, 1, n, 1);
        if(isAnomaly(1)) segTree_anomaly(1, n, 1);
        return;
    }
    segTree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_b[x] += val * segTree_siz[x];
        segTree_ab[x] += val * segTree_a[x];
        segTree_minb[x] += val;
        segTree_maxb[x] += val;
        segDelta_b[x] += val;
        return;
    }
    int mid = (cl+cr) >> 1;
    if(segTree_siz[LCH(x)]) segTree_delta_b(l, r, val, cl, mid, LCH(x));
    if(segTree_siz[RCH(x)]) segTree_delta_b(l, r, val, mid+1, cr, RCH(x));
    segTree_maintain(x);
}

LL segTree_qres;
void segTree_query_ab(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_qres = 0;
        segTree_query_ab(l, r, 1, n, 1);
        return;
    }
    
    segTree_pushdown(x);
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_qres += segTree_ab[x];
        return;
    }
    int mid = (cl+cr)>>1;
    if(segTree_siz[LCH(x)]) segTree_query_ab(l,r,cl,mid,LCH(x));
    if(segTree_siz[RCH(x)]) segTree_query_ab(l,r,mid+1,cr,RCH(x));
    segTree_maintain(x);
}

void segTree_query_siz(int l,int r,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_qres = 0;
        segTree_query_siz(l, r, 1, n, 1);
        return;
    }
    segTree_pushdown(x);
    if(cr <l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_qres += segTree_siz[x];
        return;
    }
    int mid = (cl+cr)>>1;
    if(segTree_siz[LCH(x)]) segTree_query_siz(l, r, cl, mid, LCH(x));
    if(segTree_siz[RCH(x)]) segTree_query_siz(l, r, mid+1, cr, RCH(x));
    segTree_maintain(x);
}



int N,M;
LL init_a[MAXN],init_b[MAXN];
//最开始的乘法有可能爆int 注意
struct Query{
    int t,l,r,v;
} qry[MAXN];

void segTree_build(int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        segTree_build(1,n,1);
        if(isAnomaly(1)) segTree_anomaly(1, n, 1);
        return;
    }
    
    segTree_erase(x);
    if(cl == cr){
        segTree_a[x] = segTree_mina[x] = segTree_maxa[x] = init_a[cl];
        segTree_b[x] = segTree_minb[x] = segTree_maxb[x] = init_b[cl];
        segTree_ab[x] = init_a[cl] * init_b[cl];
        segTree_siz[x] = 1;
    }else if(cl < cr){
        int mid = (cl + cr) >> 1;
        segTree_build(cl, mid, LCH(x));
        segTree_build(mid+1, cr, RCH(x));
        segTree_maintain(x);
    }
}



int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&N,&M) != EOF) {
        REP_1(i, N) cin >> init_a[i] >> init_b[i];
        REP_1(i, M){
            scanf(" %d %d %d",&qry[i].t,&qry[i].l,&qry[i].r);
            if(qry[i].t <= 4) scanf(" %d",&qry[i].v);
        }
        cin >> A >> B;
        n = N;
        segTree_build();
        REP_1(i, M){
            if(qry[i].t == 1){
                segTree_update_a(qry[i].l, qry[i].r, qry[i].v);
            }else if(qry[i].t == 2){
                segTree_update_b(qry[i].l, qry[i].r, qry[i].v);
            }else if(qry[i].t == 3){
                segTree_delta_a(qry[i].l, qry[i].r, qry[i].v);
            }else if(qry[i].t == 4){
                segTree_delta_b(qry[i].l, qry[i].r, qry[i].v);
            }else if(qry[i].t == 5){
                segTree_query_ab(qry[i].l, qry[i].r);
                cout << segTree_qres << '\n';
            }else if(qry[i].t == 6){
                segTree_query_siz(qry[i].l, qry[i].r);
                cout << segTree_qres << '\n';
            }
        }
    }
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
