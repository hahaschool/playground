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

typedef long long ULL;
typedef long long LL;
typedef long double LD;

#define COMBINATORICS_MOD1E9
#ifdef COMBINATORICS_MOD1E9
const LL MODER = 1000000007;
LL getmod(LL a){if(a<0||a>=MODER)a%=MODER;if(a<0)a+=MODER;return a;}
LL summod(LL a,LL b){return getmod(getmod(a)+getmod(b));}
LL mulmod(LL a,LL b){return getmod(getmod(a)*getmod(b));}
LL powmod(LL a,LL p){LL ret=1;while(p){if(p&1)ret=mulmod(ret,a);a=mulmod(a,a);p>>=1;}return ret;}
LL invmod(LL a){return powmod(a,MODER-2);}
#endif

#ifdef LOCAL_DEBUG
const int MAXN = 1555;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 2005;
#endif

namespace Hash{
    ULL getmod(ULL a,const ULL &m){if(a<0 || a>=m) a %= m;if(a<0) a += m;return a;}
    ULL summod(const ULL &a,const ULL &b,const ULL &m){return getmod(getmod(a,m)+getmod(b,m),m);}
    ULL mulmod(const ULL &a,const ULL &b,const ULL &m){return getmod(getmod(a,m)*getmod(b,m),m);}
    ULL powmod(ULL a,ULL p,const ULL &m){ULL ret = 1;while(p){if(p&1) ret = mulmod(a,ret,m);a=mulmod(a,a,m);p>>=1ULL;}return ret;}
    ULL invmod(const ULL &a,const ULL &m){return powmod(a, m-2, m);}
    
    const int HARDNESS = 1, CANDIDATE = 3;
    ULL HASHMOD[CANDIDATE] = { 2038074743ULL,2038074923ULL,2038074739ULL};
    ULL P[CANDIDATE] = {1471ULL,20719ULL,266261ULL};
    ULL pp[HARDNESS][MAXN];
    void hash_prep(){
        random_shuffle(HASHMOD, HASHMOD+CANDIDATE);
        random_shuffle(P, P+CANDIDATE);
        REP(i, HARDNESS){
            pp[i][0] = 1;
            REP_1(j,MAXN-1){
                pp[i][j] = mulmod(pp[i][j-1], P[i], HASHMOD[i]);
            }
        }
    }
    void hash_make(char *str,ULL tar[][MAXN],int len){
        REP(i, HARDNESS){
            REP(j, len){
                tar[i][j] = mulmod(str[j], pp[i][j], HASHMOD[i]);
                tar[i][j] = summod(tar[i][j-1], tar[i][j], HASHMOD[i]);
            }
        }
    }
    bool same(ULL hahA[][MAXN],int As,int At,ULL hahB[][MAXN],int Bs,int Bt,char *A, char*B){
        //        cout << "Comparing : ";
        //        for(int i = As;i <= At; i++) putchar(A[i]);
        //        cout << " & ";
        //        for(int i = Bs;i <= Bt; i++) putchar(B[i]);
        //        cout << " ";
        //
        //
        //        if(At-As+1 != Bt-Bs+1){ cout << "DIFF" << endl; return false;}
        bool flg = true;
        REP(i,HARDNESS){
            ULL Ares = hahA[i][At];
            if(As) Ares = summod(Ares, -hahA[i][As-1], HASHMOD[i]);
            ULL Bres = hahB[i][Bt];
            if(Bs) Bres = summod(Bres, -hahB[i][Bs-1], HASHMOD[i]);
            if(As < Bs) Ares = mulmod(Ares, pp[i][Bs-As], HASHMOD[i]);
            else Bres = mulmod(Bres, pp[i][As-Bs], HASHMOD[i]);
            flg &= Ares == Bres;
        }
        //if(flg) cout << "SAME" << endl;
        //else cout << "DIFF" << endl;
        return flg;
    }
};

int n,l;
char A[MAXN],B[MAXN],C[MAXN],Cr[MAXN];
ULL Ah[Hash::HARDNESS][MAXN],Bh[Hash::HARDNESS][MAXN],Ch[Hash::HARDNESS][MAXN],Crh[Hash::HARDNESS][MAXN];

LL dp[MAXN][2][MAXN];
LL ans = 0;
void solve(){
    memset(dp, 0, sizeof(dp));
    
    /*
    int i = -1;
    for(int j = i+2;j < n; j++){
        if((j-i)*2 > l) break;
        //cout << "tail:" << i+1 << ' ' << j << ':' << endl;
        if(Hash::same(Ah,i+1,j,Ch,l-2*(j-i),l-(j-i)-1,A,C) && Hash::same(Bh,i+1,j,Crh,0,j-i-1,B,Cr)){
            if((j-i)*2 == l) ans = summod(ans, 1);
        }
        if(Hash::same(Bh,i+1,j,Ch,l-2*(j-i),l-(j-i)-1,B,C) && Hash::same(Ah,i+1,j,Crh,0,j-i-1,A,Cr)){
            if((j-i)*2 == l) ans = summod(ans, 1);
        }
    }*/
    
    
    for(int i = 0;i < n; i++){
        //self creation
        if(A[i] == C[0]){
            dp[i][0][0] = 1;
        }
        if(B[i] == C[0]){
            dp[i][1][0] = 1;
        }
        
        //transition from outside
        if(i > 0){
            for(int j = 1;j < l; j++){
                if(A[i] == C[j]){
                    dp[i][0][j] = summod(dp[i-1][0][j-1], dp[i][0][j]);
                }
                if(B[i] == C[j]){
                    dp[i][1][j] = summod(dp[i-1][1][j-1], dp[i][1][j]);
                }
            }
        }
        
        //transition cross
        for(int j = l-1;j >= 1; j--){
            if(A[i] == C[j]){
                dp[i][0][j] = summod(dp[i][1][j-1], dp[i][0][j]);
            }
            if(B[i] == C[j]){
                dp[i][1][j] = summod(dp[i][0][j-1], dp[i][1][j]);
            }
        }
        
        
        if(i > 0){
            for(int j = i-1;j >= 0; j--){
                if((i-j+1)*2 > l) break;
                if(Hash::same(Bh,j,i,Crh,l-(i-j+1),l-1,B,Cr) && Hash::same(Ah,j,i,Ch,i-j+1,i-j+(i-j+1),A,C)){
                    dp[i][0][i-j+(i-j+1)] = summod(dp[i][0][i-j+(i-j+1)], 1);
                }
                if(Hash::same(Ah,j,i,Crh,l-(i-j+1),l-1,A,Cr) && Hash::same(Bh,j,i,Ch,i-j+1,i-j+(i-j+1),B,C)){
                    dp[i][1][i-j+(i-j+1)] = summod(dp[i][1][i-j+(i-j+1)], 1);
                }
            }
        }
        
        //after loop
        if(i < n-2){
            for(int j = i+2;j < n; j++){
                if((j-i)*2 > l) break;
                //cout << "tail:" << i+1 << ' ' << j << ':' << endl;
                if(Hash::same(Ah,i+1,j,Ch,l-2*(j-i),l-(j-i)-1,A,C) && Hash::same(Bh,i+1,j,Crh,0,j-i-1,B,Cr)){
                    //if((j-i)*2 == l) ans = summod(ans, 1);
                    ans = summod(ans,dp[i][0][l-2*(j-i)-1]);
                }
                if(Hash::same(Bh,i+1,j,Ch,l-2*(j-i),l-(j-i)-1,B,C) && Hash::same(Ah,i+1,j,Crh,0,j-i-1,A,Cr)){
                    //if((j-i)*2 == l) ans = summod(ans, 1);
                    ans = summod(ans,dp[i][1][l-2*(j-i)-1]);
                }
            }
        }
        
        
        
        ans = summod(dp[i][0][l-1], ans);
        ans = summod(dp[i][1][l-1], ans);
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    Hash::hash_prep();
    while (scanf(" %s %s %s",A,B,C) != EOF) {
        n = strlen(A);
        l = strlen(C);
        memcpy(Cr, C, sizeof(C));
        reverse(Cr,Cr+l);
        Hash::hash_make(A, Ah, n);
        Hash::hash_make(B, Bh, n);
        Hash::hash_make(C, Ch, l);
        Hash::hash_make(Cr, Crh, l);
        ans = 0;
        if(l > 2){
            solve();
            reverse(A, A+n);
            reverse(B, B+n);
            Hash::hash_make(A, Ah, n);
            Hash::hash_make(B, Bh, n);
            solve();
            cout << ans << endl;
        }else{
            if(l == 1){
                REP(i, n) if(A[i] == C[0]) ans++;
                REP(i, n) if(B[i] == C[0]) ans++;
            }else{
                REP(i,n-1) if(A[i] == C[0] && A[i+1] == C[1]) ans++;
                REP(i,n-1) if(B[i] == C[0] && B[i+1] == C[1]) ans++;
                for(int i = n-1;i > 0; i--) if(A[i] == C[0] && A[i-1] == C[1]) ans++;
                for(int i = n-1;i > 0; i--) if(B[i] == C[0] && B[i-1] == C[1]) ans++;
                REP(i,n) if(A[i] == C[0] && B[i] == C[1]) ans++;
                REP(i,n) if(B[i] == C[0] && A[i] == C[1]) ans++;
                
            }
            cout << ans << endl;
        }
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
