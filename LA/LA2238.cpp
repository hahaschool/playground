//
//  LA2238.cpp
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

int const MAXN = 505,INF = 0x3f3f3f3f;
int W[MAXN][MAXN],S[MAXN],T[MAXN],Lx[MAXN],Ly[MAXN],My[MAXN],Mx[MAXN],slack[MAXN],nx,ny;
int m,n;
bool KM_aug(int u){
    S[u] = true;
    for (int v = 1; v <= ny; v++) {
        if(!T[v]){
            int wt = Lx[u] + Ly[v] - W[u][v];
            if (!wt) {
                T[v] = true;
                if(!My[v] || KM_aug(My[v])){
                    My[v] = u;
                    Mx[u] = v;
                    return true;
                }
            }else {
                slack[v] = min(slack[v],wt);
            }
        }
    }
    return false;
}
void KM_upd(){
    int slk = INF;
    for(int i = 1; i <= ny; i++){
        if(!T[i]){
            slk = min(slk,slack[i]);
        }
    }
    for(int i = 1; i <= nx; i++){
        if(S[i]){
            Lx[i] -= slk;
        }
    }
    for(int i = 1;i <= ny; i++){
        if (T[i]) {
            Ly[i] += slk;
        }
        slack[i] = INF;
    }
}
void KM_init(){
    for(int i = 1; i <= nx; i++){
        Mx[i] = 0;
        Lx[i] = -INF;
        for(int j = 1; j <= ny; j++){
            Lx[i] = max(Lx[i],W[i][j]);
        }
    }
    for(int i = 1; i <= ny; i++){
        Ly[i] = My[i] = 0;
    }
}
void KM_flush(){
    for(int i = 1; i <= nx; i++){
        S[i] = false;
    }
    for(int i = 1; i <= ny; i++){
        T[i] = false;
    }
}
void KM(){
    KM_init();
    for(int i = 1; i <= nx; i++){
        for(int j = 1; j <= ny; j++){
            slack[j] = INF;
        }
        while (true) {
            KM_flush();
            if (KM_aug(i)) {
                break;
            }
            KM_upd();
        }
    }
}



int memsize[15];
struct Program{
    int k,s[15],t[15];
} prog[55];

int gid(int memid,int revorder){
    return (memid-1)*n+revorder;
}

void solve(){
    nx = n,ny = n*m;
    for(int i = 1;i <= nx; i++){
        for(int j = 1;j <= ny; j++){
            W[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= prog[i].k; k++){
                if(prog[i].s[k] <= memsize[j]){
                    for(int l = 1; l <= n; l++){
                        W[i][gid(j,l)] = 1000000-prog[i].t[k]*l;
                    }
                }else break;
            }
        }
    }
    KM();
    double sum = 0;
    for(int i = 1;i <= nx; i++){
        sum += Lx[i];
    }
    for(int i = 1; i <= ny; i++){
        sum += Ly[i];
    }
    sum = nx * 1000000 - sum;
    printf("Average turnaround time =  %.2lf\n",(double)sum/n);
    
    int seq[15][55],tk[15][55];
    memset(seq, -1, sizeof(seq));
    for(int i = 1; i<= nx; i++){
        int mem = Mx[i]/n+1;
        int rev = Mx[i]%n;
        if (!rev) {
            mem--;
            rev = n;
        }
        for(int k = 1;k <= prog[i].k; k++){
            if (prog[i].s[k] <= memsize[mem] && (1000000 - Lx[i] - Ly[Mx[i]])%rev == 0) {
                tk[mem][rev] = (1000000- Lx[i] - Ly[Mx[i]])/rev;
            }
        }
        seq[mem][rev] = i;
    }
    int tfrom[15][55],tto[15][55];
    memset(tfrom, 0, sizeof(tfrom));
    memset(tto, 0, sizeof(tto));
    for(int i = 1; i <= m; i++){
        for (int j = n; j >= 1; j--) {
            if (seq[i][j] != -1) {
                tfrom[i][j] = tto[i][j+1];
                tto[i][j] = tfrom[i][j] + tk[i][j];
            }
        }
    }
    for(int i = 1; i<= nx; i++){
        int mem = Mx[i]/n+1;
        int rev = Mx[i]%n;
        if (!rev) {
            mem--;
            rev = n;
        }
        printf("Program %d runs in region %d from %d to %d\n",i,mem,tfrom[mem][rev],tto[mem][rev]);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d %d",&m,&n) != EOF){
        if (m == 0 && n == 0) {
            break;
        }
        printf("Case %d\n",++caseCnt);
        for(int i = 1; i <= m; i++){
            scanf(" %d",&memsize[i]);
        }
        for(int i = 1; i <= n; i++){
            scanf(" %d",&prog[i].k);
            for(int j = 1; j <= prog[i].k; j++){
                scanf(" %d %d",&prog[i].s[j],&prog[i].t[j]);
            }
        }
        solve();
        
    }
    return 0;
}