//
//  UVA1658.cpp
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

const int MAXN = 2005,MAXE = MAXN*MAXN,INF = 0x3f3f3f3f;
int head[MAXN],ed[MAXE],nxt[MAXE],cap[MAXE],cst[MAXE],frm[MAXE],q;
int n;
void clr(){
    for(int i = 1; i <= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void ade(int f,int t,int c,int w){
    frm[q] = f;
    cap[q] = c;
    cst[q] = w;
    ed[q] = t;
    nxt[q] = head[f];
    head[f] = q++;
}
void nfade(int f,int t,int c,int w){
    ade(f, t, c, w);
    ade(t, f, 0, -w);
}

int dis[MAXN],pre[MAXN],aug[MAXN];//pre stores edgeid
bool inque[MAXN];
bool SPFA(int start,int end,int &flow,int &cost){
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        inque[i] = false;
        pre[i] = -1;
        
    }
    dis[start] = 0,inque[start] = true,aug[start] = INF;
    queue<int> que;
    que.push(start);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if (cap[i] && dis[v] > dis[u] + cst[i]) {
                dis[v] = dis[u] + cst[i];
                pre[v] = i;
                aug[v] = min(aug[u],cap[i]);
                if (!inque[v]) {
                    que.push(v);
                    inque[v] =true;
                }
            }
        }
    }
    
    if (dis[end] == INF) {
        return false;
    }
    
    flow += aug[end];
    cost += dis[end] * aug[end];
    int u = end;
    while (u != start) {
        //backtrack
        cap[pre[u]] -= aug[end];
        cap[pre[u]^1] += aug[end];
        u = frm[pre[u]];
    }
    return true;
}
int MCMF(int start,int end){
    int flow = 0,cost = 0;
    while (SPFA(start, end, flow, cost));
    return cost;
}

int N,M;
int id[MAXN][2];
int ss,tt;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while (scanf(" %d %d",&N,&M) != EOF) {
        n = (N-2)*2+4;
        clr();
        int tot = 2;
        id[1][0] = id[1][1] = 1;
        for(int i = 2; i<= N-1; i++){
            id[i][0] = tot++;
            id[i][1] = tot++;
            nfade(id[i][0], id[i][1], 1, 0);
        }
        id[N][0] = id[N][1] = n-2;
        ss = n-1;
        tt = n;
        for(int i = 1; i<= M; i++){
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            nfade(id[a][1], id[b][0], 1, c);
        }
        nfade(ss, id[1][0], 2, 0);
        nfade(id[N][0], tt, 2, 0);
        int res = MCMF(ss, tt);
        printf("%d\n",res);
    }
    
    
    return 0;
}
