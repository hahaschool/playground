//
//  LA2531.cpp
//  playground
//
//  Created by 張正昊 on 11/3/2016.
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

const int MAXN = 555,MAXE = MAXN*MAXN,INF = 0x3f3f3f3f;
int head[MAXN],ed[MAXE],nxt[MAXE],cap[MAXE],q;
int n;
void clr(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void ade(int f,int t,int c){
    ed[q] = t;
    cap[q] = c;
    nxt[q] = head[f];
    head[f] = q++;
}
void nfade(int f,int t,int c){
    ade(f,t,c);
    ade(t,f,0);
}
bool vis[MAXN];
int dis[MAXN];
bool dinic_bfs(int start,int end){
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    vis[start] = true;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int i = head[u];i;i = nxt[i]){
            int v = ed[i];
            if (!vis[v] && cap[i]) {
                dis[v] = dis[u] + 1;
                vis[v] = true;
                que.push(v);
            }
        }
    }
    return vis[end];
}
int cur[MAXN];
int dinic_dfs(int u,int a,int start,int end){
    if (u == end || a == 0) {
        return a;
    }
    int flow = 0,f;
    for(int &i = cur[u];i;i = nxt[i]){
        int v =  ed[i];
        if(dis[u] + 1 == dis[v] &&
           (f = dinic_dfs(v, min(a,cap[i]), start, end)) > 0){
            flow += f;
            a -= f;
            cap[i] -= f;
            cap[i^1] += f;
            if (a == 0) {
                break;
            }
        }
    }
    return flow;
}
int dinic(int start,int end){
    int ret = 0;
    while (dinic_bfs(start, end)) {
        for(int i = 1; i <= n; i++){
            cur[i] = head[i];
        }
        ret += dinic_dfs(start, INF, start, end);
    }
    return ret;
}

int N,ss,tt;
int WIN[30],LOSE[30],REM[30][30];
bool OK[30];

void buildgph(int acp,int asc){
    clr();
    ss = N+1,tt = N+2;
    n = N+2;
    for (int i = 1; i <= N; i++) {
        if (i == acp) {
            continue;
        }
        for (int j = i+1; j <= N; j++) {
            if (j == acp) {
                continue;
            }
            if (REM[i][j]) {
                nfade(ss, ++n, REM[i][j]);
                nfade(n, i, INF);
                nfade(n, j, INF);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        if (i == acp) {
            continue;
        }
        nfade(i, tt, asc + WIN[acp] - WIN[i]);
        //cout << "++++++ " << asc + WIN[acp] - WIN[i]  << "asc: " << asc << " acp: " << acp  << "i: " << i << endl;
    }
}

void solve(){
    int total = 0,mx = -1;
    for (int i = 1; i<= N; i++) {
        mx = max(mx,WIN[i]);
    }
    for (int i = 1; i <= N; i++) {
        for(int j = i+1;j <= N; j++){
            total += REM[i][j];
        }
    }
    memset(OK, 0, sizeof(OK));
    int cnt = 0;
    for(int i = 1;i <= N; i++){
        int mxsc = 0;
        for(int j = 1; j<= N; j++){
            mxsc += REM[i][j];
        }
        if (WIN[i] + mxsc < mx) {
            continue;
        }
        buildgph(i,mxsc);
        if (dinic(ss, tt) == total - mxsc) {
            OK[i] = true;
            cnt++;
        }
    }
    for (int i = 1; i <= N; i++) {
        if (OK[i]) {
            printf("%d",i);
            if (--cnt) {
                putchar(' ');
            }else{
                puts("");
            }
        }
    }
}



int main(){
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        scanf(" %d",&N);
        for(int i = 1; i <= N; i++){
            scanf(" %d %d",&WIN[i],&LOSE[i]);
        }
        for (int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++){
                scanf(" %d",&REM[i][j]);
            }
        }
        solve();
    }
    return 0;
}
