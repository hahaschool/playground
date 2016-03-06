//
//  LA3212.cpp
//  playground
//
//  Created by 張正昊 on 6/3/2016.
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

const int MAXN = 2005,MAXE = 40005;
int n,m;
int head[MAXN],ed[MAXE],nxt[MAXE],q;
void clr(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void ae(int f,int t){
    ed[q] = t;
    nxt[q] = head[f];
    head[f] = q++;
}

int color[MAXN];
bool judgebip(int u,int cl){
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if (color[v] == -1) {
            color[v] = cl^1;
            if (!judgebip(v,cl^1)) {
                return false;
            }
        }else{
            if (color[u] == color[v]) {
                return false;
            }
        }
    }
    return true;
}

int S[MAXN],T[MAXN],Mx[MAXN],My[MAXN],W[MAXN][MAXN],Nx,Ny;
bool aug(int u){
    S[u] = true;
    for(int v = 1;v <= Ny; v++){
        if (W[u][v] && !T[v]) {
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
void flh(){
    for(int i = 1; i <= Nx; i++){
        S[i] = 0;
    }
    for(int i = 1; i<= Ny; i++){
        T[i] =0;
    }
}
void init(){
    for(int i = 1; i <= Nx; i++){
        S[i] = 0;
        Mx[i] = 0;
    }
    for(int i = 1; i<= Ny; i++){
        T[i] =0;
        My[i] = 0;
    }
}
int hangary(){
    init();
    int ret = 0;
    for(int i = 1; i<= Nx; i++){
        flh();
        if (aug(i)) {
            ret++;
        }
    }
    return ret;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d %d",&n,&m) != EOF) {
        clr();
        for(int i = 1; i<= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            ae(a,b);
            ae(b,a);
        }
        memset(color, -1, sizeof(color));
        bool flg = true;
        for(int i = 1; i<= n; i++){
            if (color[i] == -1) {
                flg &= judgebip(i, 1);
            }
        }
        if (!flg) {
            puts("Impossible");
        }else{
            memset(W, 0, sizeof(W));
            Nx = Ny = n;
            for(int i = 1; i <= n; i++){
                if (color[i] == 0) {
                    //Nx++;
                    for(int j = head[i];j;j = nxt[j]){
                        int v = ed[j];
                        W[i][v] = 1;
                    }
                }else{
                    //Ny++;
                }
                
            }
            printf("%d\n",hangary());
        }
    }
    
    return 0;
}
