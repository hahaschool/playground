//
//  LA4043.cpp
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

const int MAXN = 105,INF = 0x3f3f3f3f;
double EPS = 1e-6;
struct Point{
    int x,y;
} px[MAXN],py[MAXN];
int n;

bool S[MAXN],T[MAXN];
int match[MAXN];
double slack[MAXN];
double W[MAXN][MAXN];
double Lx[MAXN],Ly[MAXN];
bool augment(int u){
    S[u] = true;
    for (int v = 1; v <= n; v++) {
        double wt = Lx[u] + Ly[v] - W[u][v];
        if (!T[v]) {
            if(abs(wt) < EPS){
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
    double slk = INF;
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
        Ly[i] = match[i] = 0;
        Lx[i] = -INF;
        for (int j = 1; j <= n; j++) {
            Lx[i] = max(Lx[i],W[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            slack[j] = INF;
        }
        while (true) {
            for (int j = 1; j <= n;j++) {
                S[j] = T[j] = false;
            }
            if (augment(i)) {
                break;
            }else{
                update();
            }
        }
    }
}

double dis(int a,int b){
    return sqrt(((px[a].x-py[b].x)*(px[a].x-py[b].x))+((px[a].y-py[b].y)*(px[a].y-py[b].y)));
}

void solve(){
    for (int i = 1; i <= n; i++) {
        for(int j = 1;j <= n; j++){
            W[i][j] = -dis(i,j);
        }
    }
    KM();
    int rev[MAXN];
    for (int i = 1; i <= n; i++) {
        rev[match[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n",rev[i]);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d",&n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf(" %d %d",&px[i].x,&px[i].y);
        }
        for (int i = 1; i <= n; i++) {
            scanf(" %d %d",&py[i].x,&py[i].y);
        }
        solve();
    }
    
    
    
    return 0;
}