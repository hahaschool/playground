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
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef long long LL;
typedef long double LD;

#ifdef USUAL_MOD1E9
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

const int MAXN = 1005;
int n,m,tot;
struct Item{
    int name,price;
    bool operator < (const Item &b) const{
        return price > b.price;
    }
} item[MAXN];
int num[MAXN];
int required[MAXN],optional[MAXN];


LD bin[MAXN][MAXN];
void prepbin(){
    bin[0][0] = 1;
    for(int i = 1;i < MAXN; i++){
        bin[i][0] = 1;
        for(int j = 1;j <= i; j++){
            bin[i][j] = bin[i-1][j] + bin[i-1][j-1];
        }
    }
}

LD dp[MAXN][MAXN];
void solve(){
    sort(item+1, item+1+tot);
    memset(required, 0, sizeof(required));
    memset(optional, 0, sizeof(optional));
    int reqtot = 0,opttot = 0;
    REP_1(i, tot){
        if(item[i].price > item[n].price){
            required[item[i].name]++;
            reqtot++;
        }else if(item[i].price == item[n].price){
            optional[item[i].name]++;
            item[++opttot] = item[i];
        }else{
            break;
        }
    }
    
    LD p = 1;
    REP_1(i, m){
        p *= (LD)1/bin[num[i]][required[i]];
    }
    
    memset(dp, 0, sizeof(dp));
    dp[0][0] = p;
    for(int i = 0;i < opttot; i++){
        for (int j = 0; j < min(i+1,n-reqtot+1); j++) {
            dp[i+1][j+1] += dp[i][j] * (LD)(required[item[i+1].name]+1)/(LD)(num[item[i+1].name]-required[item[i+1].name]) * (LD)(j+1)/(LD)(i+1);
            dp[i+1][j] += dp[i][j] * (LD)(i-j+1)/(LD)(i+1);
        }
        
    }
    
    cout << fixed << setprecision(12) << dp[opttot][n-reqtot] << endl;
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    prepbin();
    while (cin >> n >> m) {
        tot = 0;
        REP_1(i, m){
            ADHOC_CIN(int, a);
            num[i] = a;
            REP_1(j, a){
                ADHOC_CIN(int, p);
                item[++tot] = {i,p};
            }
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
