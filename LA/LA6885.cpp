//
//  LA6885.cpp
//  playground
//
//  Created by 張正昊 on 4/5/2016.
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

const int MAXN = 10005,MAXE = 250005,INF = 0x3f3f3f3f;
int head[MAXN],ed[MAXE*2],nxt[MAXE*2],len[MAXE*2],q;
int n,m;
void init(){
    q = 2;
    for(int i  = 1; i <= n; i++){
        head[i] = 0;
    }
}
void ade(int f,int t,int l){
    len[q] = l;
    ed[q] = t;
    nxt[q] = head[f];
    head[f] = q++;
}

bool inque[MAXN];
void SPFA(int src,int *dis){
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        inque[i] = false;
        dis[i] = INF;
    }
    dis[src] = 0;
    que.push(src);
    inque[src] = true;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;
        for(int i = head[u];i;i = nxt[i]){
            int v = ed[i];
            if(dis[u] + len[i] < dis[v]){
                dis[v] = dis[u] + len[i];
                if(!inque[v]){
                    que.push(v);
                    inque[v] = true;
                }
            }
        }
    }
}


struct State{
    int u,dis;
    State(int a,int b){
        u = a,dis = b;
    }
    bool operator < (const State &b) const{
        return dis > b.dis;
    }
};
void dijkstra(int src,int *dis){
    priority_queue<State> que;
    for (int i = 1; i <= n; i++) {
        inque[i] = false;
        dis[i] = INF;
    }
    dis[src] = 0;
    que.push(State(src,0));
    while (!que.empty()) {
        int u = que.top().u;
        que.pop();
        inque[u] = true;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if (dis[u] + len[i] < dis[v]) {
                dis[v] = dis[u] + len[i];
                que.push(State(v,dis[v]));
            }
        }
    }
}


int dis1[MAXN],dis2[MAXN];
struct Edge{
    int u,v,l;
} edge[MAXE];

void solve(){
    SPFA(1, dis1);
    SPFA(n, dis2);
    int res = 0;
    for (int i = 1; i <= m; i++) {
        int u = edge[i].u,v = edge[i].v,l = edge[i].l;
        if (dis1[u] + l + dis2[v] == dis1[n] || dis1[v] + l + dis2[u] == dis1[n]) {
            res += l;
        }
    }
    printf("%d\n",2*res);
}

int main(){
    while (scanf(" %d %d",&n,&m) != EOF) {
        init();
        for (int i = 1; i <= m; i++) {
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            a++,b++;
            edge[i] = (Edge){a,b,c};
            ade(a, b, c);
            ade(b, a, c);
        }
        solve();
    }
    return 0;
}
