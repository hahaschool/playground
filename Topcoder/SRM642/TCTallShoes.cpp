//
//  TCTallShoes.cpp
//  playground
//
//  Created by 張正昊 on 24/5/2016.
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

class TallShoes{
public:
    static const int MAXN = 55,INF = 0x3f3f3f3f;
    static const long long INFF = 0x3f3f3f3f3f3f3f3fLL;
    long long mat_cst[MAXN][MAXN];
    int mat_lvl[MAXN][MAXN];
    bool mat_lnk[MAXN][MAXN];
    int N;
    long long B;
    
    bool check(long long mid){
        //rebuild
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if(mat_lnk[i][j]){
                    long long lvl = mat_lvl[i][j];
                    if(lvl < mid){
                        mat_cst[i][j] = (long long)(mid-lvl)*(long long)(mid-lvl);
                    }else{
                        mat_cst[i][j] = 0;
                    }
                }else{
                    mat_cst[i][j] = INFF;
                }
            }
        }
        //floyd
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    mat_cst[i][j] = min(mat_cst[i][j],mat_cst[i][k] + mat_cst[k][j]);
                }
            }
        }
        return mat_cst[1][N] <= B;
    }
    
    int maxHeight(int _N,vector<int> _X,vector<int> _Y,vector<int> _height,long long _B){
        //init
        memset(mat_lnk, 0, sizeof(mat_lnk));
        
        N = _N,B = _B;
        int mih = INF,mxh = 0;
        for (int i = 0; i < _X.size(); i++) {
            for (int j = 0; j < _Y.size(); j++) {
                mat_lnk[_X[i]+1][_Y[i]+1] = mat_lnk[_Y[i]+1][_X[i]+1] = true;
                mat_lvl[_X[i]+1][_Y[i]+1] = mat_lvl[_Y[i]+1][_X[i]+1] = _height[i];
                mih = min(mih,_height[i]);
                mxh = max(mxh,_height[i]);
            }
        }
        
        long long l = mih,r = mxh+sqrt(B),mid;
        while (l+1<r) {
            mid = r - (r-l)/2;
            if (check(mid)) {
                l = mid;
            }else{
                r = mid-1;
            }
        }
        if(check(r)){
            return r;
        }
        return l;
    }
    TallShoes(){}
};

TallShoes solver;

void commitTest(int a,vector<int> b,vector<int> c,vector<int> d,long long e){
    cout << solver.maxHeight(a, b, c, d, e) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest(3
    ,{0, 1, 0}
    ,{1, 2, 2}
    ,{3, 4, 2}
               ,1);
    commitTest(3
    ,{0, 1, 0}
    ,{1, 2, 2}
    ,{3, 4, 2}
               ,52);
    commitTest(8
    ,{0, 0, 3, 3, 4, 4, 4, 7, 7}
    ,{1, 2, 1, 2, 3, 5, 6, 5, 6}
    ,{1000, 1000, 1000, 1000, 1, 1000, 1000, 1000, 1000}
               ,3);
    commitTest(10
    ,{0,1,2,3,4,5,6,7,8}
    ,{1,2,3,4,5,6,7,8,9}
    ,{0,0,0,0,0,0,0,0,0}
               ,9876543210123);
    commitTest(6
    ,{0,0,0,0,0,1,1,1,1,2,2,2,3,3,4}
    ,{1,2,3,4,5,2,3,4,5,3,4,5,4,5,5}
    ,{999999,986588,976757,988569,977678,999999,967675,947856,955856,999999,975956,956687,999999,979687,999999}
    ,          0);
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
