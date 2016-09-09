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


using namespace std;

typedef long long LL;

const int MAXN = 1000005;
int n,m,k;
LL cnt[MAXN];
LL fac2[MAXN];
const LL MODER = 1000000007;
int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    fac2[0] = 1;
    for(int i = 1;i < MAXN; i++){
        fac2[i] = fac2[i-1]*2LL;
        fac2[i] %= MODER;
    }
    
    scanf(" %d %d %d",&n,&m,&k);
    bool legal = true;
    int cl = n+1,cr = 0;
    REP_1(i, m){
        int u,v;
        scanf(" %d %d",&u,&v);
        
        if(u+1 == v){
            //normal
            continue;
        }else if(u+k+1 == v){
            //special
            cl = min(cl,u);
            cr = max(cr,u);
            cnt[u]++;
            if(cnt[u]>1) legal = false;
        }else{
            //abnormal
            legal = false;
        }
    }
    if(cr-cl > k) legal = false;
    if(!legal){
        puts("0");
    }else{
        LL res = !cr;
        for(int i = 1;i <= n; i++){
            cnt[i] += cnt[i-1];
        }
        for(int i = 1;i+k+1 <= n; i++){
            if(i <= cl && min(i+k,n-k-1) >= cr){
                res += fac2[(min(i+k,n-k-1)-i)-(cnt[min(i+k,n-k-1)] - cnt[i])];
                res %= MODER;
            }
        }
        res %= MODER;
        cout << res << endl;
    }
    
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
