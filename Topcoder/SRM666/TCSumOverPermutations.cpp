//
//  TCSumOverPermutations.cpp
//  playground
//
//  Created by 張正昊 on 18/5/2016.
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

class SumOverPermutations{
public:
    typedef long long LL;
    static const LL MODER = 1000000007,MAXN = 4004;
    LL C[MAXN][MAXN];
    inline LL MOD(LL a){
        if(a >= MODER || a < 0) a%=MODER;
        if(a<0) a+= MODER;
        return a;
    }
    LL mul_mod(LL a,LL b){
        return MOD(MOD(a)*MOD(b));
    }
    LL add_mod(LL a,LL b){
        return MOD(MOD(a)+MOD(b));
    }
    void prepare(){
        for(int i = 0;i < MAXN; i++){
            for (int j = 0; j < MAXN; j++) {
                if(!j) C[i][j] = 1;
                else if(j > i) C[i][j] = 0;
                else C[i][j] = add_mod(C[i-1][j-1],C[i-1][j]);
            }
        }
    }
    
    LL dp[MAXN][2][2];
    LL N;
    LL getd(int n,int adjL,int adjR){
        if(dp[n][adjL][adjR] != -1) return dp[n][adjL][adjR];
        LL ret = 0;
        for (int i = 1; i <= n; i++) {
            LL self = N;
            if (i == 1 && adjL) {
                self--;
            }
            if (i == n && adjR){
                self--;
            }
            
            LL tmp = mul_mod(getd(i-1,adjL,1), getd(n-i,1,adjR));
            tmp = mul_mod(tmp, C[n-1][i-1]);
            tmp = mul_mod(tmp, self);
            ret = add_mod(ret, tmp);
        }
        if (adjL + adjR == 1) dp[n][adjL^1][adjR^1] = ret;
        return dp[n][adjL][adjR] = ret;
    }
    
    int findSum(int n){
        N = n;
        memset(dp, -1, sizeof(dp));
        dp[0][0][0] = dp[0][1][0] = dp[0][0][1] = dp[0][1][1] = 1;
        return getd(n,0,0);
    }
    SumOverPermutations(){
        prepare();
    }
};

SumOverPermutations solver;


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.findSum(2) << endl;
    cout << solver.findSum(3) << endl;
    cout << solver.findSum(10) << endl;
    cout << solver.findSum(3900) << endl;
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
