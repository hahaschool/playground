//
//  UVA11383.cpp
//  playground
//
//  Created by 張正昊 on 3/3/2016.
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

const int MAXN = 505,INF = 0x3f3f3f3f;
int S[MAXN],T[MAXN];
int W[MAXN][MAXN];
int slack[MAXN];
int match[MAXN];
int Lx[MAXN],Ly[MAXN];
int n;
bool augment(int u){
    S[u] = true;
    for(int v = 1; v <= n; v++){
        if (!T[v]) {
            int wt = Lx[u] + Ly[v] - W[u][v];
            if (!wt) {
                T[v] = true;
                if (!match[v] || augment(match[v])) {
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
    int slk = INF;
    for (int i = 1; i <= n; i++) {
        if (!T[i]) {
            slk = min(slk,slack[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (S[i]) {
            Lx[i] -= slk;
        }
        if (T[i]) {
            Ly[i] += slk;
        }
        slack[i] = INF;
    }
}
void KM(){
    for (int i = 1; i <= n; i++) {
        Lx[i] = -INF;
        Ly[i] = match[i] = 0;
        for(int j = 1; j <= n; j++){
            Lx[i] = max(Lx[i],W[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        while (true) {
            for (int j = 1; j <= n; j++) {
                S[j] = T[j] = false;
            }
            if (augment(i)) {
                break;
            }
            update();
        }
    }
}

void solve(){
    KM();
    int sum = 0;
    for(int i = 1; i <= n; i++){
        sum += Lx[i];
        printf("%d",Lx[i]);
        if (i != n) {
            putchar(' ');
        }
    }
    puts("");
    for(int i = 1; i <= n; i++){
        sum += Ly[i];
        printf("%d",Ly[i]);
        if(i != n){
            putchar(' ');
        }
    }
    puts("");
    printf("%d\n",sum);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d",&n) != EOF){
        for(int i = 1;i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf(" %d",&W[i][j]);
            }
        }
        solve();
    }
    
    return 0;
}