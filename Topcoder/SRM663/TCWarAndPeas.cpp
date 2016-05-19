//
//  TCWarAndPeas.cpp
//  playground
//
//  Created by 張正昊 on 15/5/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
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

using namespace std;

class WarAndPeas{
public:
    typedef long long LL;
    static const LL MODER = 1000000007;
    LL add_mod(LL a,LL b){
        if(a>=MODER) a%=MODER;
        if(b>=MODER) b%=MODER;
        LL ret = (a+b)%MODER;
        if(ret<0) ret += MODER;
        return ret;
    }
    LL sub_mod(LL a,LL b){
        return add_mod(a, -b);
    }
    LL mul_mod(LL a,LL b){
        if(a>=MODER) a%=MODER;
        if(b>=MODER) b%=MODER;
        LL ret = (a*b)%MODER;
        if(ret<0) ret += MODER;
        return ret;
    }
    LL pow_mod(LL a,LL p){
        LL ret = 1,fac = a;
        while(p){
            if(p&1) ret=mul_mod(ret, fac);
            fac = mul_mod(fac, fac);
            p >>= 1;
        }
        return ret;
    }
    LL inv_mod(LL a){
        return pow_mod(a, MODER-2);
    }
    LL div_mod(LL a,LL b){
        return mul_mod(a, inv_mod(b));
    }
    
    static const int MAXN = 1005;
    LL N,M,S,A[MAXN],B[MAXN],F[MAXN];
    LL POW2[MAXN],INV_POW2[MAXN],C[MAXN][MAXN];
    inline LL P(LL x){
        return mul_mod(C[N-1][x], INV_POW2[N-1]);
    }
    inline LL sustain(LL good){
        LL bad = N - good - 1;
        return div_mod(add_mod(add_mod(C[good][2], C[bad][2]),good), M);
    }
    inline LL good_override(LL good){
        LL bad = N - good - 1;
        return add_mod(div_mod(bad, M), div_mod(mul_mod(good, bad), mul_mod(M, 2)));
    }
    inline LL bad_override(LL good){
        LL bad = N - good - 1;
        return div_mod(mul_mod(good, bad), mul_mod(M, 2));
    }
    int solve(){
        if (S == N-1) {
            return div_mod(1, 2);
        }
        A[0] = div_mod(P(0), sub_mod(1, sustain(0)));
        B[0] = div_mod(bad_override(1), sub_mod(1, sustain(0)));
        for (int i = 1; i < N; i++) {
            A[i] = div_mod(add_mod(P(i), mul_mod(good_override(i-1), A[i-1])), sub_mod(1, add_mod(sustain(i), mul_mod(good_override(i-1), B[i-1]))));
            B[i] = div_mod(bad_override(i+1),sub_mod(1, add_mod(sustain(i), mul_mod(good_override(i-1), B[i-1]))));
        }
        F[N-1] = A[N-1];
        for (int i = N-2; i >= 0; i--) {
            F[i] = add_mod(A[i], mul_mod(B[i], F[i+1]));
        }
        return div_mod(F[S], mul_mod(C[N-1][S],2));
    }
    int expectedPeas(string state){
        S = 0;
        for (int i = 1;i < state.size(); i++) {
            if (state[i] == state[0]) {
                S++;
            }
        }
        N = state.size(),M = C[N][2];
        return solve();
    }
    WarAndPeas(){
        //预处理2的幂及其逆元和组合数C[n][r]
        POW2[0] = 1;
        for(int i = 1;i < MAXN; i++){
            POW2[i] = mul_mod(POW2[i-1], 2);
        }
        INV_POW2[MAXN-1] = inv_mod(POW2[MAXN-1]);
        for (int i = MAXN-2; i >= 0; i--) {
            INV_POW2[i] = mul_mod(INV_POW2[i+1], 2);
        }
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if(j == 0) C[i][j] = 1;
                else if(j > i) C[i][j] = 0;
                else C[i][j] = add_mod(C[i-1][j-1], C[i-1][j]);
            }
        }
    }
};

WarAndPeas solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    string str;
    while (cin >> str) {
        cout << solver.expectedPeas(str) << endl;
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
