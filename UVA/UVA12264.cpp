//
//  UVA12264.cpp
//  playground
//
//  Created by 張正昊 on 10/3/2016.
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

const int MAXN = 105,INF = 0x3f3f3f3f;
int S[MAXN],T[MAXN],Lx[MAXN],Ly[MAXN],Mx[MAXN],My[MAXN],Nx,Ny,W[MAXN][MAXN],slack[MAXN];
void init(){
    for(int i = 1; i <= Nx;i++){
        Mx[i] = 0;
        Lx[i] = -INF;
        for(int j = 1; j <= Ny; j++){
            Lx[i] = max(Lx[i],W[i][j]);
        }
    }
    for(int i = 1;i <= Ny; i++){
        My[i] = Ly[i] = 0;
    }
}
void flh(){
    for(int i = 1; i <= Nx; i++){
        S[i] = 0;
    }
    for(int i = 1; i <= Ny; i++){
        T[i] = 0;
    }
}
bool aug(int u){
    S[u] = true;
    for(int v = 1; v <= Ny; v++){
        if (!T[v]) {
            int wt = Lx[u] + Ly[v] - W[u][v];
            if (!wt) {
                T[v] = true;
                if (!My[v] || aug(My[v])) {
                    My[v] = u;
                    Mx[u] = v;
                    return true;
                }
            }else{
                slack[v] = min(slack[v],wt);
            }
        }
    }
    return false;
}
void upd(){
    int slk = INF;
    for(int i = 1; i<= Ny; i++){
        if (!T[i]) {
            slk = min(slk,slack[i]);
        }
    }
    for(int i = 1; i <= Nx; i++){
        if (S[i]) {
            Lx[i] -= slk;
        }
    }
    for(int i = 1; i<= Ny; i++){
        if (T[i]) {
            Ly[i] += slk;
        }
        slack[i] = INF;
    }
}
void KM(){
    init();
    for(int i = 1; i<= Nx; i++){
        for(int j = 1; j <= Ny; j++){
            slack[j] = INF;
        }
        while (true) {
            flh();
            if (aug(i)) {
                break;
            }
            upd();
        }
    }
}

int n;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF && n) {
        Nx = Ny = n;
        for (int i = 0; i<= n; i++) {
            for(int j = 0; j <= n; j++){
                W[i][j] = -INF;
            }
        }
        for(int i = 1; i<= n; i++){
            int arg1,arg2;
            while (scanf(" %d",&arg1) && arg1) {
                scanf(" %d",&arg2);
                //ISSUE:When there is an edge connecting to one point itself, should not skip it!FUCK!
                    W[i][arg1] = max(W[i][arg1],-arg2);
            }
        }
        KM();
        int res = 0,flg = 1;
        for(int i = 1; i <= n; i++){
            if (W[My[i]][i] == -INF) {
                flg = 0;
                break;
            }
            res += W[My[i]][i];
        }
        if (!flg) {
            printf("N\n");
            continue;
        }
        printf("%d\n",-res);
    }
    return 0;
}
