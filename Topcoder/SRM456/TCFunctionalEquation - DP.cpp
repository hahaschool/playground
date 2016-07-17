//
//  TCFunctionalEquation.cpp
//  playground
//
//  Created by 張正昊 on 17/7/2016.
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

class FunctionalEquation{
public:
    long long X[10005],Y[10005];
    int C,N;
    
    inline long long get_mod(long long a,long long m){
        if(a >= m || a < 0) a %= m;
        if(a < 0) a += m;
        return a;
    }
    long long add_mod(long long a,long long b,long long m){
        return get_mod(get_mod(a, m) + get_mod(b, m), m);
    }
    long long mul_mod(long long a,long long b,long long m){
        return get_mod(get_mod(a, m) * get_mod(b, m), m);
    }
    
    
    
    static const int MAXN = 20;
    static const long long INF = 1000000000000000000LL;
    bool S[MAXN],T[MAXN];
    long long W[MAXN][MAXN];
    long long slack[MAXN];
    int match[MAXN];
    long long Lx[MAXN],Ly[MAXN];
    int n;
    bool augment(int u){
        S[u] = true;
        for(int v = 0;v < n; v++){
            if(!T[v]){
                long long wt = Lx[u] + Ly[v] - W[u][v];
                if(!wt){
                    T[v] = true;
                    if(match[v] == -1 || augment(match[v])){
                        match[v] = u;
                        return true;
                    }
                }else{
                    slack[v] = min(slack[v],wt);
                }
            }
        }
        return false;
    }
    void update(){
        long long slk = INF;
        for(int i = 0;i < n;i++){
            if(!T[i]) slk = min(slk,slack[i]);
        }
        for (int i = 0; i < n; i++) {
            if(S[i]) Lx[i] -= slk;
            if(T[i]) Ly[i] += slk;
            slack[i] = INF;
        }
    }
    void KM(){
        for (int i = 0; i < n; i++) {
            Lx[i] = -INF;
            Ly[i] = 0, match[i] = -1;
            for(int j = 0;j < n; j++){
                Lx[i] = max(Lx[i],W[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            while (true) {
                for (int j = 0; j < n; j++) {
                    S[j] = T[j] = false;
                }
                if(augment(i)){
                    break;
                }
                update();
            }
        }
    }
    
    long long solve(){
        //Calculate Cost of Match
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                vector<long long> vec;
                for (int k = 0; k < N; k++) {
                    if(X[k]%(2*C) == 2*i) vec.push_back(X[k]-Y[k]+j-i);
                    else if(X[k]%(2*C) == 2*j+1) vec.push_back(Y[k]-X[k]+j-i-C+1);
                }
                if (!vec.size()){
                    W[i][j] = 0;
                    continue;
                }
                sort(vec.begin(), vec.end());
                
                //medium m = kC+b,gonna minus kC for every item
                long long b = get_mod(vec[vec.size()/2], C);
                long long kC = vec[vec.size()/2] - b;
                long long res1 = 0, res2 = 0;
                for (int k = 0; k < vec.size(); k++) {
                    vec[k] -= kC, res1 += abs(vec[k]);
                    vec[k] -= C, res2 += abs(vec[k]);
                }
                W[i][j] = min(res1,res2);
            }
        }
        
        
         //DP-Bipmatch
         long long DP[1<<16];
         for(int i = 0;i < (1 << C);i++){
         DP[i] = INF;
         }
         DP[0] = 0;
         for (int i = 1; i < (1 << C); i++) {
         int cnt = 0;
         for(int j = 0;j < C;j++) if(i&(1<<j)) cnt++;
         for(int j = 0;j < C;j++) if(i&(1<<j)) DP[i] = min(DP[i],DP[i-(1<<j)] + W[cnt-1][j]);
         }
         return DP[(1<<C)-1];
         
    }
    
    long long minAbsSum(int _C,int _N,int _xzero,int _xprod,int _xadd,int _xmod,int _yzero,int _yprod,int _yadd,int _ymod){
        C = _C,N = _N;
        X[0] = _xzero,Y[0] = _yzero;
        for (int i = 1; i < N; i++) {
            X[i] = get_mod(add_mod(mul_mod(X[i-1], _xprod, _xmod),_xadd,_xmod),_xmod);
            Y[i] = get_mod(add_mod(mul_mod(Y[i-1], _yprod, _ymod),_yadd,_ymod),_ymod);
        }
        return solve();
    }
    FunctionalEquation(){
        
    }
};

FunctionalEquation solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    //cout << solver.minAbsSum(3, 10000, 564817402, 142750431, 382045455, 729267237, 37853113, 86806113, 82137026, 98560398) << endl;//0
    //cout << solver.minAbsSum(7, 9853, 100, 1, 100, 1000, 32154215, 3252151, 24512515, 141536326) << endl;//5
    cout << solver.minAbsSum(16, 10000, 37, 22, 36, 64, 54, 34, 10, 77) << endl;//3150803357206
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
