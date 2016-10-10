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

int N;
double seq[MAXN];
double apd[MAXN];
int siz;
double sum;

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (cin >> N) {
        siz = 1;
        sum = 0;
        memset(apd, 0, sizeof(apd));
        memset(seq, 0, sizeof(seq));
        REP_1(i, N){
            int typ,arg1,arg2;
            cin >> typ;
            if(typ == 1){
                cin >> arg1 >> arg2;
                apd[min(arg1,siz)] += arg2;
                sum += (double)min(arg1,siz) * (double)arg2;
            }else if(typ == 2){
                cin >> arg1;
                seq[++siz] = arg1;
                sum += arg1;
            }else{
                sum -= seq[siz] + apd[siz];
                apd[siz-1] += apd[siz];
                apd[siz] = 0;
                siz--;
            }
            cout << fixed << setprecision(10) << sum/(double)siz << endl;
        }
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
