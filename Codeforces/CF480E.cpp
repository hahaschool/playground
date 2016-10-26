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
#define ARR_SET(arr,content) memset(arr,content,sizeof(arr));

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
const int MAXN = 10;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 2005;
#endif

int N,M,K;
char brd[MAXN][MAXN];
int res[MAXN];
struct Event{
    int r,c,id;
} evt[MAXN];

int du[MAXN][MAXN],dd[MAXN][MAXN];

void dnq(int u,int d){
    if(d == u){
        int curans = 0;
        int rem = 0;
        REP_1(j, M){
            if(brd[d][j] == '.'){
                curans = 1;
                rem++;
            }
        }
        REP(i, K){
            if(evt[i].r == d){
                rem--;
                if(!rem) curans = 0;
            }
            res[i] = max(res[i],curans);
        }
    }else{
        
        static char tmpbrd[MAXN];
        int curans = 0;
        int mid = (d+u)>>1;
        dnq(u, mid);
        dnq(mid+1, d);
        //cout << u << ' ' << d << ':' << endl;
        static int up[MAXN],dn[MAXN];
        REP_1(j, M) {
            up[j] = min(du[mid][j],mid-u);
            dn[j] = min(dd[mid][j],d-mid);
            tmpbrd[j] = brd[mid][j];
        }
        //REP_1(j, M) cout << up[j] << ' ';cout << endl;
        //REP_1(j, M) cout << dn[j] << ' ';cout << endl;
        
        int l = 1, r = 1;
        struct Node{
            int pos,val;
        };
        static Node que_up[MAXN],que_dn[MAXN];
        
        curans = 0;
        int head_up = 0,tail_up = 0,head_dn = 0,tail_dn = 0;
        while(tmpbrd[l] == 'X') l++,r++;
        que_up[tail_up++] = {l,up[l]};
        que_dn[tail_dn++] = {l,dn[l]};
        while(l <= M){
            //eliminate expired items
            while(head_up < tail_up && que_up[head_up].pos < l) head_up++;
            while(head_dn < tail_dn && que_dn[head_dn].pos < l) head_dn++;
            
            while(que_up[head_up].val + que_dn[head_dn].val + 1 >= r-l+1){
                //cout << '|' << que_up[head_up].val + que_dn[head_dn].val + 1 << '|' << r-l+1 << endl;
                curans = max(r-l+1,curans);
                if(r == M || tmpbrd[r+1] == 'X') break;
                //try extend r
                r++;
                while(head_up < tail_up && que_up[tail_up-1].val >= up[r]) tail_up--;
                que_up[tail_up++] = {r,up[r]};
                while(head_dn < tail_dn && que_dn[tail_dn-1].val >= dn[r]) tail_dn--;
                que_dn[tail_dn++] = {r,dn[r]};
            }
            while(l == r && r < M && tmpbrd[r+1] == 'X') l++,r++;
            l++;
        }
        //cout << "BEF" << curans << endl;
        
        REP_1(i, K){
            //cout << "EVT" << i << ':' << endl;
            if(evt[i].r <= d && evt[i].r >= u){
                if(evt[i].r == mid) tmpbrd[evt[i].c] = 'X';
                else if(evt[i].r < mid) up[evt[i].c] = min(up[evt[i].c],mid-evt[i].r-1);
                else if(evt[i].r > mid) dn[evt[i].c] = min(dn[evt[i].c],evt[i].r-mid-1);
                
                //REP_1(j, M) cout << up[j] << ' ';cout << endl;
                //REP_1(j, M) cout << dn[j] << ' ';cout << endl;
                
                curans = 0;
                l = r = 1;
                int head_up = 0,tail_up = 0,head_dn = 0,tail_dn = 0;
                while(tmpbrd[l] == 'X') l++,r++;
                que_up[tail_up++] = {l,up[l]};
                que_dn[tail_dn++] = {l,dn[l]};
                while(l <= M){
                    //eliminate expired items
                    while(head_up < tail_up && que_up[head_up].pos < l) head_up++;
                    while(head_dn < tail_dn && que_dn[head_dn].pos < l) head_dn++;
                    
                    while(que_up[head_up].val + que_dn[head_dn].val + 1 >= r-l+1){
                        //cout << l << ' ' << r  << ' ' ;
                       //cout << '|' << que_up[head_up].val + que_dn[head_dn].val + 1 << '|' << r-l+1 << endl;
                        curans = max(r-l+1,curans);
                        if(r == M || tmpbrd[r+1] == 'X') break;
                        //try extend r
                        r++;
                        while(head_up < tail_up && que_up[tail_up-1].val >= up[r]) tail_up--;
                        que_up[tail_up++] = {r,up[r]};
                        while(head_dn < tail_dn && que_dn[tail_dn-1].val >= dn[r]) tail_dn--;
                        que_dn[tail_dn++] = {r,dn[r]};
                    }
                    while(l == r && r < M && tmpbrd[r+1] == 'X') l++,r++;
                    l++;
                }
                
                
            }
            //cout << curans << endl;
            res[i] = max(res[i],curans);
        }
    }
    
}

void solve(){
    ARR_SET(res, 0);
    ARR_SET(du, 0);
    REP_1(j, M){
        int cnt = 0;
        REP_1(i, N){
            du[i][j] = cnt;
            if(brd[i][j] == '.') cnt++;
            else cnt = 0;
        }
    }
    ARR_SET(dd, 0);
    REP_1(j, M){
        int cnt = 0;
        REP_1R(i, N){
            dd[i][j] = cnt;
            if(brd[i][j] == '.') cnt++;
            else cnt = 0;
        }
    }
    dnq(1,N);
    REP_1(i, K) cout << res[i] << endl;
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d %d",&N,&M,&K) != EOF) {
        REP_1(i, N) REP_1(j, M) scanf(" %c",&brd[i][j]);
        REP_1(i, K){
            ADHOC_SCANINT(r);ADHOC_SCANINT(c);
            evt[i] = {r,c,i};
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
