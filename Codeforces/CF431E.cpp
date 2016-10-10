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

#ifdef LOCAL_DEBUG
const int MAXN = 105;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 200005;
#endif

#pragma mark TREAP
struct Node{
    int rnd;
    int lch,rch;
    LL val,siz,sum,rep;
    void clear(){
        lch = rch = -1;
        rnd = rand();
        val = siz = sum = rep = 0;
    }
} treap[MAXN];
int tot,root;
void init(){
    root = -1;
    tot = 0;
}
int alloc(){
    tot++;
    treap[tot].clear();
    return tot;
}
void maintain(int k){
    LL siz = treap[k].rep;
    if(treap[k].lch != -1) siz += treap[treap[k].lch].siz;
    if(treap[k].rch != -1) siz += treap[treap[k].rch].siz;
    treap[k].siz = siz;
    
    LL sum = treap[k].val * treap[k].rep;
    if(treap[k].lch != -1) sum += treap[treap[k].lch].sum;
    if(treap[k].rch != -1) sum += treap[treap[k].rch].sum;
    treap[k].sum = sum;
}
void rturn(int &k){
    int t = treap[k].lch;
    treap[k].lch = treap[t].rch;
    treap[t].rch = k;
    maintain(k);maintain(t);
    k = t;
}
void lturn(int &k){
    int t = treap[k].rch;
    treap[k].rch = treap[t].lch;
    treap[t].lch = k;
    maintain(k);maintain(t);
    k = t;
}

void insert(int &k,LL x){
    if(k == -1){
        k = alloc();
        treap[k].siz = treap[k].rep = 1;
        treap[k].val = treap[k].sum = x;
        return;
    }
    
    treap[k].siz++;
    treap[k].sum += x;
    
    if(treap[k].val == x) treap[k].rep++;
    else if(x > treap[k].val){
        insert(treap[k].rch, x);
        if(treap[treap[k].rch].rnd < treap[k].rnd){
            lturn(k);
        }
    }else{
        insert(treap[k].lch, x);
        if(treap[treap[k].lch].rnd < treap[k].rnd){
            rturn(k);
        }
    }
}

//Must ensure x in the tree
void remove(int &k,LL x){
    if(k == -1) return;
    if(treap[k].val == x){
        if(treap[k].rep > 1){
            treap[k].rep--;
            treap[k].siz--;
            treap[k].sum -= x;
            return;
        }
        if(treap[k].lch == -1 || treap[k].rch == -1){
            k = (treap[k].lch == -1)?treap[k].rch:treap[k].lch;
        }else if(treap[treap[k].lch].rnd < treap[treap[k].rch].rnd){
            rturn(k);
            remove(k,x);
        }else{
            lturn(k);
            remove(k,x);
        }
    }else if(x > treap[k].val){
        treap[k].siz--;
        treap[k].sum -= x;
        remove(treap[k].rch,x);
    }else{
        treap[k].siz--;
        treap[k].sum -= x;
        remove(treap[k].lch,x);
    }
}

LL count(int k,LL x){
    if(k == -1) return 0;
    if(treap[k].val == x) return treap[k].rep;
    if(x > treap[k].val){
        return count(treap[k].rch,x);
    }else{
        return count(treap[k].lch,x);
    }
}

double query_sum(int k,double x){
    if(k == -1) return 0;
    double ret = 0;
    if(x < treap[k].val){
        ret += query_sum(treap[k].lch, x);
        return ret;
    }else{
        if(treap[k].lch != -1) ret += treap[treap[k].lch].sum;
        ret += (double)treap[k].val * treap[k].rep;
        ret += query_sum(treap[k].rch, x);
        return ret;
    }
}

double query_siz(int k,double x){
    if(k == -1) return 0;
    double ret = 0;
    if(x < treap[k].val){
        ret += query_siz(treap[k].lch, x);
        return ret;
    }else{
        if(treap[k].lch != -1) ret += treap[treap[k].lch].siz;
        ret += (double)treap[k].rep;
        ret += query_siz(treap[k].rch,x);
        return ret;
    }
}

LL N,Q;
LL seq[MAXN];

bool check(double mid,double arg){
    //cout << "mid=" << mid << " arg=" << arg << " siz=" << query_siz(root, mid) << " sum=" << query_sum(root, mid) << endl;
    double require = query_siz(root, mid) * mid - query_sum(root, mid);
    return arg < require;
}

double solve(double arg){
    double l = 0,r = 1e17,mid;
    REP(i,100){
        mid = (l+r)/2.0;
        if(check(mid,arg)){
            r = mid;
        }else{
            l = mid;
        }
    }
    return l;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    srand(time(NULL));
    while (cin >> N >> Q) {
        init();
        REP_1(i, N){
            cin >> seq[i];
            insert(root, seq[i]);
        }
        REP_1(i, Q){
            LL typ,arg1,arg2;
            cin >> typ >> arg1;
            if(typ == 1){
                cin >> arg2;
                remove(root, seq[arg1]);
                seq[arg1] = arg2;
                insert(root, arg2);
            }else{
                cout << fixed << setprecision(10) << solve(arg1) << endl;
            }
        }
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
