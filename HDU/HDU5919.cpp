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

const int MAXN = 200005;
int ch[MAXN*20][2],seg_siz[MAXN*20],rev[MAXN];
int n,m;
int tot,revtot;
void clr(int x){
    seg_siz[x] = 0;
    ch[x][0] = ch[x][1] = -1;
}
int alloc(){
    clr(tot);
    return tot++;
}

void clone(int src,int dst){
    ch[dst][0] = ch[src][0];
    ch[dst][1] = ch[src][1];
    seg_siz[dst] = seg_siz[src];
}

void maintain(int x){
    int sz = 0;
    if(ch[x][0] != -1) sz += seg_siz[ch[x][0]];
    if(ch[x][1] != -1) sz += seg_siz[ch[x][1]];
    seg_siz[x] = sz;
}



int seq[MAXN],prv[MAXN],pos[MAXN];

void tree_init(int cl = -1,int cr = -1,int cur = -1){
    if(cur == -1){
        tot = revtot = 0;
        rev[revtot++] = alloc();
        tree_init(1,n,rev[0]);
        return;
    }
    if(cl == cr){
        seg_siz[cur] = 0;
    }else if(cl < cr){
        int mid = (cl+cr)>>1;
        int lch = ch[cur][0] = alloc();
        int rch = ch[cur][1] = alloc();
        tree_init(cl,mid,lch);
        tree_init(mid+1,cr,rch);
        maintain(cur);
    }
}

void tree_build(int cl = -1,int cr = -1,int cur = -1){
    if(cur == -1){
        int rt = rev[revtot++] = alloc();
        clone(rev[0], rt);
        tree_build(1,n,rt);
        return;
    }
    if(cl == cr){
        seg_siz[cur] = prv[cl] == 0;
        return;
    }else if(cl < cr){
        int mid = (cl+cr)>>1;
        int lch = ch[cur][0] = alloc();
        int rch = ch[cur][1] = alloc();
        tree_build(cl,mid,lch);
        tree_build(mid+1,cr,rch);
        maintain(cur);
    }
}

void tree_update(int base,int pos,int val,int cl = -1,int cr = -1,int x = -1){
    if(x == -1){
        int rt = rev[revtot++] = alloc();
        clone(rev[base],rt);
        tree_update(base,pos,val,1,n,rt);
        return;
    }
    if(cr < pos || cl > pos) return;
    if(cl == pos && cr == pos){
        seg_siz[x] = val;
        return;
    }
    int mid = (cl+cr)>>1;
    if(pos <= mid){
        int lch = alloc();
        clone(ch[x][0], lch);
        ch[x][0] = lch;
        tree_update(base, pos, val, cl, mid, lch);
    }else{
        int rch = alloc();
        clone(ch[x][1], rch);
        ch[x][1] = rch;
        tree_update(base, pos, val, mid+1, cr, rch);
    }
    maintain(x);
}

int qres;
void siz_query(int lrv,int rrv,int l,int r, int cl = -1,int cr = -1,int lx = -1,int rx = -1){
    if(lx == -1){
        qres = 0;
        siz_query(lrv, rrv, l, r, 1, n, rev[lrv], rev[rrv]);
        return;
    }
    if(cr < l || cl > r) return;
    if(cl >= l && cr <= r){
        qres += seg_siz[rx] - seg_siz[lx];
        return;
    }
    int mid = (cl+cr)>>1;
    int llch = ch[lx][0], lrch = ch[lx][1];
    int rlch = ch[rx][0], rrch = ch[rx][1];
    siz_query(lrv, rrv, l, r, cl, mid, llch, rlch);
    siz_query(lrv, rrv, l, r, mid+1, cr, lrch, rrch);
}

int rngkth_query(int lrv,int rrv,int l,int r,int k,int cl = -1,int cr = -1,int lx = -1,int rx = -1){
    if(lx == -1){
        qres = 0;
        return rngkth_query(lrv, rrv, l, r, k, 1,n,rev[lrv],rev[rrv]);
    }
    if(cr < l || cl > r) return 0;
    int mid = (cl+cr)>>1;
    if(cl >= l && cr <= r){
        if(k <= 0){
            return seg_siz[rx] - seg_siz[lx];
        }
        if(cl == cr){
            if(seg_siz[rx] - seg_siz[lx] == 1){
                if(k == 1){
                    qres = cl;
                }
                return 1;
            }
            return 0;
        }
        
        int incl = seg_siz[ch[rx][0]] - seg_siz[ch[lx][0]];
        int incr = seg_siz[ch[rx][1]] - seg_siz[ch[lx][1]];
        if(incl + incr < k) return incl+incr;
        if(incl >= k){
            //go into l
            rngkth_query(lrv, rrv, l, r, k, cl, mid, ch[lx][0], ch[rx][0]);
            
        }else{
            //go into r
            rngkth_query(lrv, rrv, l, r, k-incl, mid+1, cr, ch[lx][1], ch[rx][1]);
            
        }
        return incl+incr;
    }
    
    //attempt to achieve k in lch
    int incl = rngkth_query(lrv, rrv, l, r, k, cl, mid, ch[lx][0], ch[rx][0]);
    
    //only can achieve k in rch
    int incr = rngkth_query(lrv, rrv, l, r, k-incl, mid+1, cr, ch[lx][1], ch[rx][1]);
    
    return incl + incr;
}



inline bool scan_d(int &num){
    char in;bool IsN=false;
    in=getchar();
    if(in==EOF) return false;
    while(in!='-'&&(in<'0'||in>'9')) in=getchar();
    if(in=='-'){ IsN=true;num=0;} else num=in-'0';
    while(in=getchar(),in>='0'&&in<='9') num*=10,num+=in-'0';
    if(IsN) num=-num;
    return true;
}



int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int ___;
    scan_d(___);
    for(int __ = 1;__ <= ___; __++){
        printf("Case #%d:",__);
        scanf(" %d %d",&n,&m);
        tree_init();
        REP_1(i, n) scan_d(seq[i]);
        memset(prv, 0, sizeof(prv));
        memset(pos, 0, sizeof(pos));
        REP_1(i, n) {
            prv[i] = pos[seq[i]];
            pos[seq[i]] = i;
        }
        tree_build();
        memset(pos, 0, sizeof(pos));
        REP_1(i, n) pos[prv[i]] = i;
        REP_1(i, n) {
            if(pos[i]) tree_update(i, pos[i], 1);
            else {
                int pv = revtot-1;
                rev[revtot++] = rev[pv];
            }
        }
        
        int ans = 0;
        REP_1(i, m){
            int l,r;scan_d(l);scan_d(r);
            int ll = min((l+ans)%n+1,(r+ans)%n+1);
            int rr = max((l+ans)%n+1,(r+ans)%n+1);
            //cout << "proceeding : " << ll << ' ' << rr << endl;
            siz_query(0, ll, ll, rr);
            int k = (qres+1)/2;
            rngkth_query(0, ll, ll, rr, k);
            printf(" %d",qres);
            ans = qres;
        }
        puts("");
    }
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
