//
//  LA3126.cpp
//  playground
//
//  Created by 張正昊 on 4/3/2016.
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

const int MAXN = 505;
struct Customer{
    int time,sx,sy,tx,ty;
} cus[MAXN];
int n;
int mht(int xa,int ya,int xb,int yb){
    return abs(xa-xb) + abs(ya-yb);
}
int tim(int hh,int mm){
    return hh*60+mm;
}

int S[MAXN],T[MAXN],Mx[MAXN],My[MAXN],W[MAXN][MAXN],Nx,Ny;
bool aug(int u){
    S[u] = true;
    for(int v = 1; v <= Ny; v++){
        if (!T[v] && W[u][v]) {
            T[v] = true;
            if (!My[v] || aug(My[v])) {
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
void init(){
    for(int i = 1; i <= Nx; i++){
        Mx[i] = 0;
    }
    for(int i = 1; i <= Ny; i++){
        My[i] = 0;
    }
}
void flh(){
    for(int i = 1;i <= Nx; i++){
        S[i] = false;
    }
    for(int i = 1; i <= Ny; i++){
        T[i] = false;
    }
}
int hungary(){
    init();
    int ret = 0;
    for(int i  =1 ;i<= Nx; i++){
        flh();
        if (aug(i)) {
            ret++;
        }
    }
    return ret;
}


void solve(){
    Nx = Ny = n;
    for(int i = 1; i<= n; i++){
        for(int j = 1; j<= n; j++){
            W[i][j] = 0;
        }
    }
    for(int i = 1; i<= n; i++){
        int duri = mht(cus[i].sx, cus[i].sy, cus[i].tx, cus[i].ty);
        for(int j = 1; j <= n; j++){
            if (i != j) {
                int durj = mht(cus[i].tx, cus[i].ty, cus[j].sx, cus[j].sy);
                if (cus[i].time + duri + durj < cus[j].time) {
                    W[i][j] = 1;
                }
            }
        }
    }
    printf("%d\n",n-hungary());
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf("%d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        scanf(" %d",&n);
        for(int i = 1; i <= n; i++){
            int h,m;
            scanf(" %d:%d",&h,&m);
            cus[i].time = tim(h,m);
            scanf(" %d %d %d %d",&cus[i].sx,&cus[i].sy,&cus[i].tx,&cus[i].ty);
        }
        solve();
    }
    
    return 0;
}