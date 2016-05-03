//
//  UVA11542.cpp
//  playground
//
//  Created by 張正昊 on 29/4/2016.
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

const int MAXN = 105;
typedef int Matrix[MAXN][MAXN];


int prime[MAXN],primetot;
bool isprime[505];
void genprime(){
    memset(isprime, true, sizeof(isprime));
    for (int i = 2; i < 500; i++) {
        if(isprime[i]){
            prime[++primetot] = i;
            for (int j = i+i; j <= 500; j+=i) {
                isprime[j] = false;
            }
        }
    }
}

long long seq[MAXN];
int cnt[MAXN][MAXN];
void decomp(int x){
    long long cx = seq[x];
    for (int i = 1; i <= primetot; i++) {
        cnt[x][i] = 0;
        while (cx % prime[i] == 0) {
            cnt[x][i]++;
            cx /= prime[i];
        }
    }
}

Matrix Mat;

int gauss(Matrix A,int equ,int var){
    int row,col,freevar = 0;
    for(row = 0,col = 0;row < equ && col < var;row++,col++){
        int mxr = row;
        for(int i = row+1;i < equ; i++){
            if(A[i][col]){
                mxr = i;
                break;
            }
        }
        if(mxr != row){
            for(int i = col;i <= var; i++){
                swap(A[mxr][i], A[row][i]);
            }
        }
        if (!A[row][col]) {
            row--;
            freevar++;
            continue;
        }
        
        for(int i = row+1;i < equ;i++){
            if (A[i][col]) {
                for (int j = col; j <= var; j++) {
                    A[i][j] ^= A[row][j];
                }
            }
        }
    }
    return freevar;
}

int n;


void solve(){
    for(int i = 1; i <= n; i++){
        decomp(i);
    }
    for (int i = 0; i < primetot; i++) {
        for(int j = 0;j < n; j++){
            Mat[i][j] = cnt[j+1][i+1]&1;
        }
        Mat[i][n] = 0;
    }
    int rep = gauss(Mat, primetot, n);
    printf("%lld\n",((1LL << rep)-1));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    genprime();
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        scanf(" %d",&n);
        for (int i = 1; i <= n; i++) {
            scanf(" %lld",&seq[i]);
        }
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
