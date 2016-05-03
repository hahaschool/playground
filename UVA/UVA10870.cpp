//
//  UVA10870.cpp
//  playground
//
//  Created by 張正昊 on 27/4/2016.
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

int d,n,m;

struct Matrix{
    static const int MAXN = 16;
    int siz;
    int mat[MAXN][MAXN];
    void zero(){
        for(int i = 0 ; i < siz; i++){
            for(int j = 0; j < siz; j++){
                mat[i][j] = 0;
            }
        }
    }
    void identity(){
        zero();
        for(int i = 0 ; i < siz; i++){
            mat[i][i] = 1;
        }
    }
};

inline void domod(int &a,int &m){
    a %= m;
    if (a < 0) {
        a += m;
    }
}

Matrix mul(Matrix A,Matrix B,int mod){
    Matrix ret;
    ret.siz = A.siz;
    ret.zero();
    for (int k = 0; k < A.siz; k++) {
        for(int i = 0; i < A.siz; i++){
            for(int j = 0; j < A.siz; j++){
                ret.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                domod(ret.mat[i][j],mod);
            }
        }
    }
    return ret;
}

Matrix pow(Matrix A,int p,int mod){
    Matrix ret;
    ret.siz = A.siz;
    ret.identity();
    Matrix fac = A;
    while (p) {
        if(p&1){
            ret = mul(ret,fac,mod);
        }
        fac = mul(fac,fac,mod);
        p >>= 1;
    }
    return ret;
}

Matrix Q,R;


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while(scanf(" %d %d %d",&d,&n,&m) != EOF && d+n+m){
        Q.siz = R.siz = d;
        Q.zero();
        R.zero();
        for (int i = 0; i < d; i++) {
            scanf(" %d",&Q.mat[0][i]);
            domod(Q.mat[0][i], m);
        }
        for (int i = 1,j = 0; i < d; i++,j++) {
            Q.mat[i][j] = 1;
        }
        for (int i = d-1; i >= 0; i--) {
            scanf(" %d",&R.mat[i][0]);
            domod(R.mat[i][0], m);
        }
        if (n <= d) {
            printf("%d\n",R.mat[d-n][0]);
            continue;
        }
        Q = pow(Q,n-d,m);
        R = mul(Q, R, m);
        printf("%d\n",R.mat[0][0]);
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
