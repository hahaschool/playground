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

int N;
int cnt[26];
char buf[MAXN];


void solve(){
    int odd = 0;
    REP(i, 26){
        if(cnt[i]&1){
            odd++;
        }
    }
    if(odd>1) {
        cout << 0 << endl;
        REP(i, 26){
            REP(j,cnt[i]) putchar('a'+i);
        }
        puts("");
        return;
    }
    int g = cnt[0];
    for(int i = 1;i < 26; i++){
        g = __gcd(cnt[i],g);
    }
    if(g&1){
        cout << g << endl;
        int len = 0;
        REP(i, 26){
            len += cnt[i]/g;
        }
        int l = 0,r = len-1;
        buf[r+1] = '\0';
        char oddchr = 0;
        REP(i,26){
            if((cnt[i]&1) == 0){
                REP(j,cnt[i]/g/2){
                    buf[l] = buf[r] = 'a'+i;
                    l++,r--;
                }
            }else{
                oddchr = 'a'+i;
            }
        }
        while(l <= r){
            buf[l] = buf[r] = oddchr;
            l++,r--;
        }
        REP(i, g) cout << buf;
        cout << endl;
    }else{
        cout << g << endl;
        int len = 0,cur = 0;
        REP(i,26){
            len += cnt[i]/g;
            REP(j, cnt[i]/g) buf[cur++] = 'a'+i;
        }
        REP_R(i,len) buf[cur++] = buf[i];
        buf[cur] = '\0';
        REP(i, g/2) cout << buf;
        cout << endl;
    }
    
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (cin >> N) {
        memset(cnt, 0, sizeof(cnt));
        REP(i, N) cin >> cnt[i];
        solve();
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
