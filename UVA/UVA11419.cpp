//
//  UVA11419.cpp
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

const int MAXN = 1005;
bool S[MAXN],T[MAXN],W[MAXN][MAXN];
int Mx[MAXN],My[MAXN],Nx,Ny;
int r,c,n;
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
int hungary(){
    for (int i = 1; i<= Nx; i++) {
        S[i] = Mx[i] = 0;
    }
    for (int i = 1; i <= Ny; i++) {
        T[i] = My[i] = 0;
    }
    
    int ans = 0;
    for(int i = 1;i <= Nx; i++){
        for (int j = 1; j <= Nx; j++) {
            S[j] = 0;
        }
        for (int j = 1; j <= Ny; j++) {
            T[j] = 0;
        }
        if (aug(i)) {
            ans++;
        }
    }
    return ans;
}

bool MKRx[MAXN],MKRy[MAXN];
void mkans(int u){
    MKRx[u] = true;
    for (int v = 1; v <= Ny; v++) {
        if (!MKRy[v] && W[u][v]) {
            MKRy[v] = true;
            if (My[v]) {
                mkans(My[v]);
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d %d %d",&r,&c,&n) != EOF) {
        if (!r && !c && !n) {
            break;
        }
        Nx = r,Ny = c;
        for (int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++){
                W[i][j] = 0;
            }
        }
        for(int i = 1; i<= n; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            W[a][b] = 1;
        }
        int ans = hungary();
        printf("%d",ans);
        for (int i = 1; i <= r; i++) {
            MKRx[i] = false;
        }
        for (int i = 1; i <= c; i++) {
            MKRy[i] = false;
        }
        for(int i = 1; i <= r; i++){
            if (!Mx[i]) {
                mkans(i);
            }
        }
        for(int i = 1;i <= r; i++){
            if (!MKRx[i]) {
                printf(" r%d",i);
            }
        }
        for (int i = 1; i <= c; i++) {
            if (MKRy[i]) {
                printf(" c%d",i);
            }
        }
        puts("");
    }
    
    return 0;
}