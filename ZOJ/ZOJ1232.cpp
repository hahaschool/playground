//
//  ZOJ1232.cpp
//  playground
//
//  Created by 張正昊 on 13/3/2016.
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

const int MAXN = 105,MAXE = MAXN*MAXN,INF = 0x3f3f3f3f;
int A,B,M,L,K,n,ss,tt;
int mat[MAXN][MAXN];

int head[MAXN],nxt[MAXE],ed[MAXE],cst[MAXE],frm[MAXE],q;
void clr(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void ade(int f,int t,int c){
    cst[q] = c;
    ed[q] = t;
    frm[q] = f;
    nxt[q] = head[f];
    head[f] = q++;
}

void floyd_warshall(){
    for(int k = 1; k <= A; k++){
        for(int i = 1; i<= n; i++){
            for(int j = 1;j <= n; j++){
                mat[i][j] = min(mat[i][j],mat[i][k] + mat[k][j]);
            }
        }
    }
}

struct State{
    int u,dis,k;
    State(int l,int a,int b):u(l),dis(a),k(b){}
    bool operator < (const State &b) const{
        return dis > b.dis;
    }
};

int dis[MAXN][15];
bool vis[MAXN][15];
void SPFA(){
    queue<State> que;
    que.push(State(ss,0,K));
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[ss][K] = 0;
    while (!que.empty()) {
        int u = que.front().u;
        int uk = que.front().k;
        que.pop();
        vis[u][uk] = false;
        //try walk
        for(int i = head[u];i;i = nxt[i]){
            int v = ed[i];
            if (dis[u][uk] + cst[i] < dis[v][uk]) {
                dis[v][uk] = dis[u][uk] + cst[i];
                if (!vis[v][uk]) {
                    vis[v][uk] = true;
                    que.push(State(v,dis[v][uk],uk));
                }
            }
        }
        //try fly
        if (uk) {
            for(int v = 1; v <= n; v++){
                if (v != u && mat[u][v] <= L) {
                    if (dis[u][uk] < dis[v][uk-1]) {
                        dis[v][uk-1] = dis[u][uk];
                        if (!vis[v][uk-1]) {
                            vis[v][uk-1] = true;
                            que.push(State(v,dis[v][uk-1],uk-1));
                        }
                    }
                }
            }
        }
    }
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %d %d %d %d",&A,&B,&M,&L,&K);
        n = A+B;
        clr();
        ss = A+B,tt = 1;
        memset(mat, 0x3f, sizeof(mat));
        for (int i = 1; i <= M; i++) {
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            mat[a][b] = min(mat[a][b],c);
            mat[b][a] = min(mat[b][a],c);
        }
        for(int i = 1; i<= n;i++){
            for(int j = 1; j <= n; j++){
                if (mat[i][j] != INF) {
                    ade(i,j,mat[i][j]);
                }
            }
        }
        for(int i = 1;i <= n; i++){
            mat[i][i] = 0;
        }
        floyd_warshall();
        if (K) {
            SPFA();
            int res = INF;
            for (int i = 0; i <= K; i++) {
                res = min(res,dis[tt][i]);
            }
            printf("%d\n",res);
        }else{
            printf("%d\n",mat[ss][tt]);
        }
    }
    
    return 0;
}
