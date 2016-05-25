//
//  TCWheelofFortune.cpp
//  playground
//
//  Created by 張正昊 on 24/5/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//HARD ONE!

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

class WheelofFortune{
public:
    static const int MAXN = 305;
    int N;
    vector<int> s;
    double f[MAXN][MAXN];
    double g[MAXN][MAXN];
    double p[MAXN][MAXN];
    double solve(){
        int M = s.size();
        for (int i = 1; i < N; i++) {
            for (int j = 0; j <= M; j++) {
                for (int k = 0; k <= M; k++) {
                    g[j][k] = p[j][k] = 0;
                }
            }
            p[0][0] = 1.0;
            
            for (int j = 0; j < M; j++) {
                double q0 = (double)(max(i-s[j],0)+max(N-i-s[j],0))/(double)N;
                double q2 = (double)(max(i-N+s[j],0)+max(N-i-N+s[j],0))/(double)N;
                double q1 = (1.0-q0-q2)/2.0;
                for (int k = 0; k <= j; k++) {
                    p[j+1][k] += p[j][k]*(q0+q1);
                    p[j+1][k+1] += p[j][k]*(q1+q2);
                }
                for (int k = 0; k <= j; k++) {
                    g[j+1][k] += g[j][k]*q0;
                    g[j+1][k] += (g[j][k] + p[j][k])*q1;
                    g[j+1][k+1] += g[j][k]*q1;
                    g[j+1][k+1] += (g[j][k]+p[j][k])*q2;
                }
            }
            
            for (int x = 0; x <= M; x++) {
                f[x][i] = g[M][x];
            }
        }
        
        double ret = 0.0;
        for (int i = 0; i < M; i++) {
            //A's exp
            ret += (double)s[i]/(double)N;
        }
        for (int x = 0; x <= M; x++) {
            double mx = -1;
            for (int j = 1; j < N; j++) {
                mx = max(mx,f[x][j]);
            }
            ret += mx;
        }
        return ret;
    }
    
    double maxExpectedValue(int _N,vector<int> _s){
        N = _N,s = _s;
        return solve();
    }
    WheelofFortune(){}
};

WheelofFortune solver;
void commitTest(int a,vector<int> b){
    cout << solver.maxExpectedValue(a, b) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest(4
               ,{2});
    commitTest(6
               ,{1,1,1,1,1,1});
    commitTest(20
               ,{1,20,1,20,1});
    commitTest(10
               ,{3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5});
    commitTest(15
               ,{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
