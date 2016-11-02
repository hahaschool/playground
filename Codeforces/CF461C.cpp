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
const int MAXN = 105;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 100005;
#endif

int N,Q;
int fenwick[MAXN];
inline int lowbit(const int &a){
    return a&(-a);
}
int get(int x){
    int ret = 0;
    while(x > 0){
        ret += fenwick[x];
        x -= lowbit(x);
    }
    return ret;
}
void add(int x,int val){
    while(x <= N){
        fenwick[x] += val;
        x += lowbit(x);
    }
}


bool swp;
int l,r;
void fold(int center){
    if(swp){
        if(center > r-l-center){
            int posa = r-center, posb = posa+1;
            int nl = posa;
            while(r-center > l){
                int val = get(posa)-get(posa-1);
                add(posb,val);
                center++,posa--,posb++;
            }
            l = nl;
            swp ^= 1;
        }else{
            int posa = r-center+1, posb = posa-1;
            r = posb;
            while(center){
                int val = get(posa) - get(posa-1);
                add(posb,val);
                center--,posa++,posb--;
            }
        }
    }else{
        if(center > r-l-center){
            int posa = l+center+1,posb = posa-1;
            int nr = posb;
            while(l+center < r){
                int val = get(posa)-get(posa-1);
                add(posb,val);
                center++,posa++,posb--;
            }
            r = nr;
            swp ^= 1;
        }else{
            int posa = l+center, posb = posa+1;
            l = posa;
            while(center){
                int val = get(posa)-get(posa-1);
                add(posb,val);
                center--,posa--,posb++;
            }
        }
    }
}
int query(int ql,int qr){
    if(swp) return get(r-ql)-get(r-qr);
    return get(l+qr)-get(l+ql);
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&N,&Q) != EOF) {
        l = 0,r = N;
        swp = false;
        memset(fenwick, 0, sizeof(fenwick));
        REP_1(i,N) add(i,1);
        REP_1(i,Q){
            int typ,arg,brg;
            scanf(" %d %d",&typ,&arg);
            if(typ == 1){
                //cout << l << ' ' << r << endl;
                fold(arg);
            }else{
                scanf(" %d",&brg);
                printf("%d\n",query(arg,brg));
            }
        }
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
