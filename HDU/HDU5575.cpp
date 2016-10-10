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
typedef long long int64;

#define LCH(x) ((x) << 1)
#define RCH(x) (((x) << 1) + 1)

const int MAXN = 4888888;
int segTree[MAXN*2],segLazy[MAXN*2],segDelta[MAXN*2];
int n;

void segTree_init(){
    memset(segTree, 0, sizeof(int)*4*n);
    memset(segLazy, 0, sizeof(int)*4*n);
    memset(segDelta, 0, sizeof(int)*4*n);
}

void segTree_pushdown(int x){
    if(segDelta[x]){
        segTree[LCH(x)] += segDelta[x];
        segTree[RCH(x)] += segDelta[x];
        segDelta[LCH(x)] += segDelta[x];
        segDelta[RCH(x)] += segDelta[x];
        segDelta[x] = 0;
    }
    
    if(segLazy[x]){
        //直接把父亲节点的最大值当成懒惰标记传下去，保证是最大的，不然会出现不小心更新了不是最大值的情况
        segTree[LCH(x)] = max(segTree[LCH(x)],segTree[x]);
        segTree[RCH(x)] = max(segTree[RCH(x)],segTree[x]);
        segLazy[LCH(x)] = max(segLazy[LCH(x)],max(segTree[x],segTree[LCH(x)]));
        segLazy[RCH(x)] = max(segLazy[RCH(x)],max(segTree[x],segTree[RCH(x)]));
        segLazy[x] = 0;
    }
    
}

void segTree_update(int l,int r,int val,int cl = -1,int cr = - 1,int cur = -1){
    if(cur == -1){segTree_update(l,r,val,1,n,1);return;}
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree[cur] = max(val,segTree[cur]);
        segLazy[cur] = max(segTree[cur],segLazy[cur]);
        return;
    }
    segTree_pushdown(cur);
    int mid = (cl + cr) >> 1;
    segTree_update(l, r, val, cl, mid, LCH(cur));
    segTree_update(l, r, val, mid+1, cr, RCH(cur));
    segTree[cur] = max(segTree[LCH(cur)],segTree[RCH(cur)]);
}

void segTree_delta(int l,int r,int val,int cl = -1,int cr = -1,int cur = -1){
    if(cur == -1) {segTree_delta(l, r, val, 1, n, 1);return;}
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree[cur] += val;
        segDelta[cur] += val;
        return;
    }
    segTree_pushdown(cur);
    int mid = (cl+cr)>>1;
    segTree_delta(l, r, val, cl, mid, LCH(cur));
    segTree_delta(l, r, val, mid+1, cr, RCH(cur));
    segTree[cur] = max(segTree[LCH(cur)],segTree[RCH(cur)]);
}


int segTree_qres;
void segTree_query(int l,int r,int cl = -1,int cr = -1,int cur = -1){
    if(cur == -1){segTree_qres = 0;segTree_query(l,r,1,n,1);return;}
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        segTree_qres = max(segTree[cur],segTree_qres);
        return;
    }
    segTree_pushdown(cur);
    int mid = (cl + cr) >> 1;
    segTree_query(l, r, cl, mid, LCH(cur));
    segTree_query(l, r, mid+1, cr, RCH(cur));
}

int revdsc[MAXN];
int dsctot;
inline void dsc_init(){
    dsctot = 0;
}
inline void dsc_insert(int x){
    revdsc[dsctot++] = x;
}
inline void dsc_make(){
    sort(revdsc, revdsc+dsctot);
    dsctot = unique(revdsc, revdsc+dsctot) - revdsc;
}
inline int dsc(int x){
    return lower_bound(revdsc, revdsc+dsctot, x) - revdsc + 1;
}

struct Condition{
    int x, y, z;
    bool operator < (const Condition &b) const{
        if(x != b.x) return x < b.x;
        if(y != b.y) return y < b.y;
        return z < b.z;
    }
    
} cond[MAXN];



int N,M;
int height[MAXN/4];

struct Request{
    int l,r,val;
    bool operator < (const Request &b) const{
        if(l != b.l) return l < b.l;
        if(r != b.r) return r < b.r;
        return val < b.val;
    }
} req[MAXN],deltareq[MAXN];
int reqtot = 0,deltatot = 0;


namespace IO {
    template <class T>
    inline bool scan_d (T &ret) {
        char c;
        int sgn;
        if (c = getchar(), c == EOF) return 0; //EOF
        while (c != '-' && (c < '0' || c > '9') ) c = getchar();
        sgn = (c == '-') ? -1 : 1;
        ret = (c == '-') ? 0 : (c - '0');
        while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
        ret *= sgn;
        return 1;  
    }
};

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    //IO::begin();
    
    int ___;
    IO::scan_d(___);
    for(int __ = 1;__ <= ___; __++){
        
        printf("Case #%d: ",__);
        IO::scan_d(N);
        IO::scan_d(M);
        //scanf(" %d %d",&N,&M);
        dsc_init();
        dsc_insert(0);
        
        int mxh = 0;
        REP_1(i, N-1){
            //scanf(" %d",&height[i]);
            IO::scan_d(height[i]);
            mxh = max(mxh,height[i]);
            dsc_insert(height[i]);
        }
        
        REP_1(i, M){
            //scanf(" %d %d %d",&cond[i].x,&cond[i].y,&cond[i].z);
            IO::scan_d(cond[i].x);
            IO::scan_d(cond[i].y);
            IO::scan_d(cond[i].z);
            mxh = max(mxh,cond[i].y+1);
            dsc_insert(cond[i].y);
            dsc_insert(cond[i].y+1);
        }
        height[0] = height[N] = mxh+1;
        dsc_insert(mxh+1);
        dsc_make();
        sort(cond+1, cond+1+M);
        
        /*
        cout << endl;
        for(int i = 0;i < dsctot; i++){
            cout << revdsc[i] << ' ';
        }cout << endl;
        */
        
        n = dsctot;
        segTree_init();
        for(int cur = 1,i = 1;cur <= N; cur++){
            
            
            
            int j = i,cnt = 0;
            for(;j <= M && cond[j].x == cur; j++) cnt++;
            j--;
            if(!cnt){
                //INDEP
                segTree_query(dsc(0), dsc(height[cur-1]));
                segTree_update(dsc(0),dsc(height[cur-1]),segTree_qres);
            }else{
                reqtot = deltatot =  0;
                int fls = 0,pos = 0;
                for(int k = i;k <= j; k++) if(!cond[k].z) fls++;
                int prv = 0;
                for(int k = i;k <= j; k++){
                    //not include:prv -> Q.y
                    if(height[cur-1] < prv){
                        //ALL DIRECT
                        
                    }else if(height[cur-1] > cond[k].y){
                        segTree_query(dsc(0), dsc(height[cur-1]));
                        int a = segTree_qres;
                        req[++reqtot] = {dsc(prv),dsc(cond[k].y),a + fls + pos};
                        
                    }else{
                        //PART INDEP
                        segTree_query(dsc(0), dsc(height[cur-1]));
                        req[++reqtot] = {dsc(prv),dsc(height[cur-1]),segTree_qres + fls + pos};
                    }
                    
                    deltareq[++deltatot] = {dsc(prv), dsc(cond[k].y), fls+pos};
                    
                    //include:Q.y+1->Q+1.y
                    if(!cond[k].z) fls--; else pos++;
                    prv = cond[k].y+1;
                }
                
                if(height[cur-1] < prv){
                    //ALL DIRECT
                }else{
                    //DIRECT
                    //PART INDEP
                    segTree_query(dsc(0), dsc(height[cur-1]));
                    req[++reqtot] = {dsc(prv),dsc(height[cur-1]),segTree_qres + fls + pos};
                }
                
                deltareq[++deltatot] = {dsc(prv), dsc(mxh+1), fls+pos};
                for(int k = 1;k <= deltatot; k++){
                    segTree_delta(deltareq[k].l, deltareq[k].r, deltareq[k].val);
                }
                
                for(int k = 1; k <= reqtot; k++){
                    segTree_update(req[k].l, req[k].r, req[k].val);
                    
                }
            }
            /*
            cout << endl;
            for(int i = 1;i <= dsctot; i++){
                segTree_query(i, i);
                cout << segTree_qres << ' ';
            }cout << endl;
            */
            i = j+1;
        }
        
        segTree_query(dsc(0), dsc(mxh+1));
        printf("%d\n",segTree_qres);
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
