//
//  UVA10779.cpp
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
int head[MAXN],nxt[MAXE],ed[MAXE],cap[MAXE],q;
int n;
void clr(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void ade(int f,int t,int c){
    cap[q] = c;
    ed[q] = t;
    nxt[q] = head[f];
    head[f] = q++;
}
void nfade(int f,int t,int c){
    ade(f,t,c);
    ade(t,f,0);
}
int dis[MAXN];
bool vis[MAXN];
bool dinic_bfs(int start,int end){
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    vis[start] = true;
    while (!que.empty()) {
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
    if (u == end || !a) {
        return a;
    }
    int flow = 0,f;
    for (int i = cur[u]; i; i = nxt[i]) {
        int v = ed[i];
        if (dis[u] + 1 == dis[v] &&
            (f = dinic_dfs(v, min(cap[i],a), start, end)) > 0) {
            flow += f;
            a -= f;
            cap[i] -= f;
            cap[i^1] += f;
            if (!a) {
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

int N,M,ss,tt;
int cnt[15][30];
int itemid[30];
int personid[15];

void solve(){
    clr();
    n = 0;
    for(int i = 2; i <= N; i++){
        personid[i] = ++n;
    }
    for(int i = 1;i <= M;i++){
        itemid[i] = ++n;
    }
    ss = ++n,tt = ++n;
    for (int i = 1; i <= M; i++) {
        if (cnt[1][i]) {
            nfade(ss, itemid[i], cnt[1][i]);
        }
    }
    for (int i = 1; i <= M; i++) {
        nfade(itemid[i], tt, 1);
    }
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (!cnt[i][j]) {
                nfade(itemid[j], personid[i], 1);
            }else if(cnt[i][j] > 1){
                nfade(personid[i], itemid[j], cnt[i][j] - 1);
            }
        }
    }
    printf("%d\n",dinic(ss, tt));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        memset(cnt, 0, sizeof(cnt));
        printf("Case #%d: ",d);
        scanf(" %d %d",&N,&M);
        for (int i = 1; i <= N; i++) {
            int k;
            scanf(" %d",&k);
            for (int j = 1; j <= k; j++) {
                int c;
                scanf(" %d",&c);
                cnt[i][c]++;
            }
        }
        solve();
    }
    return 0;
}
