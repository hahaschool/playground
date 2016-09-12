//
//  CF295D.cpp
//  playground
//
//  Created by 張正昊 on 8/9/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//NTT Version
//Warning:Severely Exceeds TL(14s,TL2s),although O(n^2logn)

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

#define USUAL_MODANY
#ifdef USUAL_MODANY
inline LL getmod(LL a,LL m){if(a<0||a>=m)a%=m;if(a<0)a+=m;return a;}
inline LL summod(LL a,LL b,LL m){return getmod(getmod(a,m)+getmod(b,m),m);}
inline LL mulmod(LL a,LL b,LL m){return getmod(getmod(a,m)*getmod(b,m),m);}
inline LL powmod(LL a,LL p,LL m){LL ret=1;while(p){if(p&1)ret=mulmod(ret,a,m);a=mulmod(a,a,m);p>>=1;}return ret;}
inline LL invmod(LL a,LL m){return powmod(a,m-2,m);}
#endif

#define NTT_MOD_ANY
#ifdef NTT_MOD_ANY
// 多项式乘法 系数对MOD=1000000007取模， 常数巨大，慎用
// 只要选的K个素数乘积大于MOD*MOD*N,理论上MOD可以任取。
#define MOD 1000000007
#define K 3
//用于CRT的三个模空间
const int m[K] = {1004535809, 998244353, 104857601};
//479*2^21+1,7*17*2^23+1,25*2^22+1
//m[0] > m[1] > m[2]
#define G 3
//上述三个素数的原根

const int MAXN = 4444;

inline int qpow(int x, int k, int P) {
    int ret = 1;
    while(k) {
        if(k & 1) ret = 1LL * ret * x % P;
        k >>= 1;
        x = 1LL * x * x % P;
    }
    return ret;
}

struct _NTT {
    //wn:旋转分量 P:模空间(P-1是2的幂)
    int wn[25], P;
    //init(_P)用给出的模空间_P构建旋转分量
    void init(int _P) {
        P = _P;
        for(int i = 1; i <= 21; ++i) {
            int t = 1 << i;
            wn[i] = qpow(G, (P - 1) / t, P);
        }
    }
    
    //RADAR编码
    //FFT与IFFT之前的反转变换
    //位置i和(i的二进制反转)位置互换
    //len需要是2的幂
    void change(int *y, int len) {
        for(int i = 1, j = len / 2; i < len - 1; ++i) {
            if(i < j) swap(y[i], y[j]);
            int k = len / 2;
            while(j >= k) {
                j -= k;
                k /= 2;
            }
            j += k;
        }
    }
    
    //NTT主过程，y是等待变换的数组，下标从0开始，长度为len
    //len是2的幂
    //on=1的话NTT on=-1的话INTT
    void NTT(int *y, int len, int on) {
        change(y, len);
        int id = 0;
        
        for(int h = 2; h <= len; h <<= 1) {
            ++id;
            for(int j = 0; j < len; j += h) {
                int w = 1;
                for(int k = j; k < j + h / 2; ++k) {
                    int u = y[k];
                    int t = 1LL * y[k+h/2] * w % P;
                    y[k] = u + t;
                    if(y[k] >= P) y[k] -= P;
                    y[k+h/2] = u - t + P;
                    if(y[k+h/2] >= P) y[k+h/2] -= P;
                    w = 1LL * w * wn[id] % P;
                }
            }
        }
        if(on == -1) {
            for(int i = 1; i < len / 2; ++i) swap(y[i], y[len-i]);
            int inv = qpow(len, P - 2, P);
            for(int i = 0; i < len; ++i)
                y[i] = 1LL * y[i] * inv % P;
        }
    }
    
    //自动多项式乘法，结果将会反映到A数组
    //需要事先调整好len至大于离2n最近的2的幂
    void mul(int A[], int B[], int len) {
        NTT(A, len, 1);
        NTT(B, len, 1);
        for(int i = 0; i < len; ++i) A[i] = 1LL * A[i] * B[i] % P;
        NTT(A, len, -1);
    }
}ntt[K];

int tmp[MAXN][K], t1[MAXN], t2[MAXN];
int r[K][K];

//特殊的防爆CRT
//x = x0 + x1*p0 + x2*p0*p1 (% p0*p1*p2) [0<=x0<p0 0<=x1<p1 0<=x2<p2]
//x = a0 (% p0)
//x = a1 (% p1)
//x = a2 (% p2)

//因为我们保证p0*p1*p2>MODER*MODER*n，在P0*p1*p2模空间内，我们计算的原始数值一定只有单个映射
//我们的目的是求出x0 x1 x2,借此用另外一种形式表达x(p0p1p2混合进制形式)
//这样就可以绕开爆LL的问题

//x (%p0) = a0 (%p0) = x0 [因为x0的范围限定在[0,p0),可以看成求出了(% p0*p1*p2)中的x0]
//x (%p1) = a1 (%p1) = x0 + x1*p0 (%p1) [因为p1|p0*p1*p2,在大空间中的x0对应到小空间的位置是确定的]
// --> x1 = (a1 - x0)/p0 (%p1) [因为x1的范围限定在[0,p1),可以看成求出了(% p0*p1*p2)中的x1]
//x (%p2) = a2 (%p2) = x0 + x1*p0 + x2*p0*p1 (%p2) [同上]
// --> x2 = (a2 - x0 - x1*p0)/p0*p1 (%p2) [同上]

int CRT(int a[]) {
    int x[K];
    for(int i = 0; i < K; ++i) {
        x[i] = a[i];
        for(int j = 0; j < i; ++j) {
            int t = (x[i] - x[j]) % m[i];
            if(t < 0) t += m[i];
            x[i] = 1LL * t * r[j][i] % m[i];
        }
    }
    int mul = 1, ret = x[0] % MOD;
    for(int i = 1; i < K; ++i) {
        mul = 1LL * mul * m[i-1] % MOD;
        ret += 1LL * x[i] * mul % MOD;
        if(ret >= MOD) ret -= MOD;
    }
    return ret;
}

//自动多项式乘法，模指定的数(1e9+7)
//len需要调整到离2n最近的2的幂，下标从0开
//结果存入A[]中
//系数模1e9+7就可以
void mul(int A[], int B[], int len) {
    for(int id = 0; id < K; ++id) {
        //转储系数变量
        for(int i = 0; i < len; ++i) {
            t1[i] = A[i];
            t2[i] = B[i];
        }
        //使用id号NTT单元做多项式乘法
        ntt[id].mul(t1, t2, len);
        //转储乘法结果
        for(int i = 0; i < len; ++i)
            tmp[i][id] = t1[i];
    }
    //将乘法结果回射到指定(1e9+7)空间
    for(int i = 0; i < len; ++i) {
        A[i] = CRT(tmp[i]);
    }
}

//预处理逆元r[i][j]:m[i]在m[j]空间内逆元
//初始化需要的NTT单元
void init() {
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < i; ++j) {
            r[j][i] = qpow(m[j], m[i] - 2, m[i]);
        }
    }
    for(int i = 0; i < K; ++i) {
        ntt[i].init(m[i]);
    }
}

#endif

int N,M;
int hf[MAXN/2][MAXN/2];
void prephf2(){
    for(int w = 2;w < MAXN/2; w++){
        hf[1][w] = 1;
    }
    for(int h = 2;h < MAXN/2;h++){
        int pfx = 0;
        for(int w = 1;w < MAXN/2; w++){
            pfx = summod(pfx, hf[h-1][w],MOD);
            hf[h][w] = summod(hf[h][w-1], pfx,MOD);
        }
    }
}
int al[MAXN/2][MAXN/2];

int f[MAXN/2],g[MAXN/2],pfx[MAXN/2];
int ff[MAXN],gg[MAXN];
void prepal2(){
    for(int h = 1;h <= 2000; h++){
        al[h][2] = 1;
    }
    
    for (int w = 3; w <= 2000; w++) {
        f[0] = 0;
        g[0] = 1;
        for(int h = 1;h <= 2000; h++){
            f[h] = hf[h][w];
            pfx[h] = summod(pfx[h], hf[h][w-1], MOD);
            g[h] = summod(summod(pfx[h], g[h], MOD), hf[h][w-1], MOD);
        }
        memset(ff, 0, sizeof(ff));
        memset(gg, 0, sizeof(gg));
        for(int j = 0;j <= 2000; j++){
            ff[j] = f[j];
            gg[j] = g[j];
        }
        mul(ff, gg, 4096);
        for(int h = 0;h <= 2000; h++){
            al[h][w] = ff[h];
        }
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    init();
    prephf2();
    prepal2();
    while (cin >> N >> M) {
        LL res = 0;
        for(int h = N;h >= 1; h--){
            LL mpl = N-h+1;
            LL tmp = 0;
            for(int w = M;w >= 2;w--){
                LL mlp = M-w+1;
                tmp = summod(tmp, mulmod(mlp, al[h][w], MOD), MOD);
            }
            res = summod(res, mulmod(mpl, tmp, MOD), MOD);
        }
        cout << res << endl;
    }
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
