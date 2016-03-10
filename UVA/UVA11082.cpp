//
//  UVA11082.cpp
//  playground
//
//  Created by 張正昊 on 9/3/2016.
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
int head[MAXN],ed[MAXE],nxt[MAXE],cap[MAXE],q;
int n;
void clr(){
    for(int i = 1; i <= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void addedge(int from,int to,int capacity){
    ed[q] = to;
    cap[q] = capacity;
    nxt[q] = head[from];
    head[from] = q++;
}

bool vis[MAXN];
int dis[MAXN];
bool bfs(int start,int end){
    for(int i = 1; i<= n; i++){
        vis[i] = false;
    }
    queue<int> que;
    dis[start] = 0;
    vis[start] = true;
    que.push(start);
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int i = head[u];i;i = nxt[i]){
            int v = ed[i];
            if (!vis[v] && cap[i]) {
                vis[v] = true;
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return vis[end];
}

int cur[MAXN];
int dfs(int u,int a,int start,int end){
    if (u == end || !a) {
        return a;
    }
    int flow = 0,f;
    for(int &i = cur[u];i;i = nxt[i]){
        int v = ed[i];
        if (dis[u] + 1 == dis[v] &&
            (f = dfs(v, min(a,cap[i]), start, end)) > 0) {
            cap[i] -= f;
            cap[i^1] += f;
            flow += f;
            a -= f;
            if (!a) {
                break;
            }
        }
    }
    return flow;
}

int dinic(int start,int end){
    int flow = 0;
    while (bfs(start, end)) {
        for(int i = 1; i <= n; i++){
            cur[i] = head[i];
        }
        flow += dfs(start, INF, start, end);
    }
    return flow;
}

int mat[22][22];
int A[22],B[22],As[22],Bs[22];
int N,M;

inline void mfade(int f,int t,int c){
    addedge(f, t, c);
    addedge(t, f, 0);
}

int ss,tt;
void buildgph(){
    n = N+M+2;
    clr();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            mfade(i,N+j,19);
        }
    }
    for (int i = 1; i <= N; i++) {
        mfade(ss, i, As[i]-M);
    }
    for(int i = 1; i <= M; i++){
        mfade(N+i, tt, Bs[i]-N);
    }
}



void solve(){
    ss = N+M+1,tt = N+M+2;
    buildgph();
    int res = dinic(ss, tt);
    int ei = 2;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j<= M; j++){
            mat[i][j] = cap[ei+1]+1;
            ei += 2;
            printf("%d",mat[i][j]);
            if (j != M) {
                putchar(' ');
            }else{
                putchar('\n');
            }
        }
    }
    
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        printf("Matrix %d\n",d);
        scanf(" %d %d",&N,&M);
        for(int i = 1; i<= N; i++){
            scanf(" %d",&A[i]);
        }
        for(int i = 1; i <= M; i++){
            scanf(" %d",&B[i]);
        }
        for(int i = 1; i <= N; i++){
            As[i] = A[i] - A[i-1];
        }
        for(int i = 1; i <= M; i++){
            Bs[i] = B[i] - B[i-1];
        }
        solve();
        puts("");
    }
    
    return 0;
}
