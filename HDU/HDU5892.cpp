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

#define CLR(a,b) memset(a,0,sizeof(a));
template<typename X>
class fenwick{
    static const int MAXN = 3005;
    static inline int lowbit(const int x){return x&(-x);}
    struct tree_array_single{
        X arr[MAXN][MAXN];
        void add(int x,int y,X n){
            for(int i=x; i<MAXN; i += lowbit(i))
                for(int j=y; j<MAXN; j += lowbit(j))
                    arr[i][j]^=n;
        }
        X sum(int x,int y){
            X res=0;
            for(int i=x; i; i-=lowbit(i))
                for(int j=y; j; j-=lowbit(j))
                    res^=arr[i][j];
            return res;
        }
    } T1,T2,T3,T4;
    X xormul(X a,X b){
        if(b&1) return a;
        else return 0;
    }
    void add(int x,int y,X n){
        T1.add(x,y,n);T2.add(x,y,xormul(n,y));T3.add(x,y,xormul(n, x));T4.add(x,y,xormul(n, x*y));
    }
    
    X sum(int x,int y){
        return xormul(T1.sum(x,y), (x+1)*(y+1))^xormul(T2.sum(x,y), x+1)^xormul(T3.sum(x,y),y+1)^T4.sum(x,y);
    }
    
public:
    void init(){CLR(T1.arr,0);CLR(T2.arr,0);CLR(T3.arr,0);CLR(T4.arr,0);}
    void update(int L,int B,int R,int T,X n){
        add(L,B,n);add(L,T+1,n);add(R+1,B,n);add(R+1,T+1,n);
    }
    X query(int L,int B,int R,int T){
        return sum(R,T)^sum(L-1,T)^sum(R,B-1)^sum(L-1,B-1);
    }
};

fenwick<LL> solver;

int n,m;
void solve(){
    solver.init();
    scanf(" %d %d",&n,&m);
    REP_1(i, m){
        char op;
        int x_1,y_1,x_2,y_2,k,a,b;
        scanf(" %c %d %d %d %d",&op,&x_1,&y_1,&x_2,&y_2);
        if(op == 'P'){
            scanf(" %d",&k);
            LL msk = 0;
            REP_1(j, k){
                scanf(" %d %d",&a,&b);
                if(b&1) msk ^= (1LL<<a);
            }
            solver.update(x_1, y_1, x_2, y_2, msk);
        }else{
            LL msk = solver.query(x_1, y_1, x_2, y_2);
            for(int i = 1;i <= 50; i++){
                if(msk&(1LL<<i)) printf("2");
                else printf("1");
                putchar(' ');
                if(i == 50) puts("");
            }
        }
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    solve();
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
