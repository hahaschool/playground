//
//  HDU5727.cpp
//  playground
//
//  Created by 張正昊 on 19/7/2016.
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

const int MAXN = 11;
int N,M;
bool somber[MAXN][MAXN];//i Yang j Yin
//KM
const int INF = 0x3f3f3f3f;
int S[MAXN],T[MAXN],W[MAXN][MAXN],slack[MAXN],match[MAXN],Lx[MAXN],Ly[MAXN];
bool augment(int u){
    S[u] = true;
    for (int v = 1; v <= N; v++) {
        if(!T[v]){
            int wt = Lx[u] + Ly[v] - W[u][v];
            if(!wt){
                T[v] = true;
                if(!match[v] || augment(match[v])){
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
    for (int i = 1; i <= N; i++)
        if(!T[i]) slk = min(slk,slack[i]);
    for (int i = 1; i <= N; i++) {
        if(S[i]) Lx[i] -= slk;
        if(T[i]) Ly[i] += slk;
        slack[i] = INF;
    }
}
void KM(){
    for (int i = 1; i <= N; i++) {
        Lx[i] = -INF;
        Ly[i] = match[i] = 0;
        for (int j = 1; j <= N; j++) {
            Lx[i] = max(Lx[i],W[i][j]);
        }
    }
    for (int i = 1; i <= N; i++) {
        while(true){
            for (int j = 1; j <= N; j++) {
                S[j] = T[j] = false;
            }
            if(augment(i)){
                break;
            }
            update();
        }
    }
}

void solve(){
    if(N == 0) {
        puts("0");
        return;
    }
    int res = 0;
    vector<int> yinseq;
    yinseq.resize(N);
    for (int i = 0; i < N; i++) {
        yinseq[i] = i+1;
    }
    while (true) {
        for (int j = 1; j <= N; j++) {
            if(somber[j][yinseq[0]] || somber[j][yinseq[N-1]]) W[j][1] = 0;
            else W[j][1] = 1;
            for (int k = 2; k <= N; k++) {
                if(somber[j][yinseq[k-2]] || somber[j][yinseq[k-1]]) W[j][k] = 0;
                else W[j][k] = 1;
            }
        }
        KM();
        int ret = 0;
        for (int i = 1; i <= N; i++) {
            ret += W[match[i]][i];
        }
        res = max(ret,res);
        if(!next_permutation(yinseq.begin()+1, yinseq.end())) break;
    }
    printf("%d\n",N-res);
}

int main(){
    while (scanf(" %d %d",&N,&M) != EOF) {
        memset(somber, 0, sizeof(somber));
        for (int i = 1; i <= M; i++) {
            int a,b;
            scanf(" %d %d",&a,&b);
            somber[a][b] = true;
        }
        solve();
    }
    return 0;
}
