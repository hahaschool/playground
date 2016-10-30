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
const int MAXN = 15;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 100005;
#endif

LL N,A,Cf,Cm,M;
struct Block{
    LL lv;
    int pos;
} blk[MAXN];
bool cmp_lv(const Block &a,const Block &b){
    return a.lv < b.lv;
}
bool cmp_pos(const Block &a, const Block &b){
    return a.pos < b.pos;
}

void solve(){
    sort(blk+1, blk+1+N, cmp_lv);
    int mxpos = N+1;
    LL rem = M;
    for(int i = N;i >= 1; i--){
        if(rem >= A-blk[i].lv){
            rem -= A-blk[i].lv;
            mxpos = i;
        }else break;
    }
    if(mxpos == 1){
        cout << Cf*N+Cm*A << endl;
        REP_1(i, N) cout << A << ' ';
        cout << endl;
        return;
    }
    
    LL ans = 0;
    LL curh = 0, remh = blk[1].lv,curw = 0;
    //while(curw < mxpos-1 && blk[curw+1].lv == blk[curw].lv) curw++;
    LL ans_mxpos = N+1,ans_curw = -1,ans_curh = -1;
    while(mxpos <= N+1){
        //determine height
        while(true){
            if(rem >= curw * remh){
                rem -= curw * remh;
                curh += remh;
                remh = 0;
                
                //progress
                if(curw == mxpos-1) break;
                curw++;
                while(curw < mxpos-1 && blk[curw+1].lv == blk[curw].lv){
                    curw++;
                }
                if(curw == mxpos-1){
                    remh = A-blk[curw].lv;
                }else{
                    remh = blk[curw+1].lv - blk[curw].lv;
                }
            }else{
                LL cnt = rem / curw;
                rem -= cnt*curw;
                curh += cnt;
                remh -= cnt;
                break;
            }
        }
        
        //update answer
        if((N+1LL-(LL)mxpos)*Cf + curh*Cm > ans){
            ans = (N+1LL-(LL)mxpos)*Cf + curh*Cm;
            ans_curw = curw;
            ans_mxpos = mxpos;
            ans_curh = curh;
        }
        
        //move max cur
        rem += A-blk[mxpos].lv;
        if(curh > blk[mxpos].lv) {
            rem -= curh - blk[mxpos].lv;
            curw++;
        }
        mxpos++;
    }
    if(ans == 6255){
       // cout << ans_mxpos << ' ' << ans_curh << ' ' << ans_curw << endl;
    }
    cout << ans << endl;
    for(int i = 1;i <= ans_curw; i++){
        blk[i].lv = ans_curh;
    }
    for(int i = ans_mxpos; i <= N; i++){
        blk[i].lv = A;
    }
    sort(blk+1,blk+1+N,cmp_pos);
    for(int i = 1;i <= N; i++){
        cout << blk[i].lv << ' ' ;
    }cout << endl;
    
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (cin >> N >> A >> Cf >> Cm >> M) {
        blk[0] = {A,0};
        REP_1(i, N) {
            cin >> blk[i].lv;
            blk[i].pos = i;
        }
        blk[N+1] = {A,(int)N+1};
        solve();
    }
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
