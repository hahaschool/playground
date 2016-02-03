//
//  UVA10917.cpp
//  playground
//
//  Created by 張正昊 on 29/1/2016.
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

const int INF = 0x3f3f3f3f;
const int MAXN = 1005,MAXE = 1000005;
int n,m;
struct Graph{
int head[MAXN],nxt[MAXE],ed[MAXE],q,cst[MAXE];
void clear(){
    q = 2;
    for(int i = 1; i<= n ; i++){
        head[i] = 0;
    }
}
void addEdge(int from,int to,int len){
    cst[q] = len;
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}
} gph,reg;


long long dis[MAXN];
bool vis[MAXN];
struct cmp{
    bool operator ()(int a,int b){
        return dis[a] > dis[b];
    }
};
void dijkstra(int src){
    for(int i = 1; i <= n;  i++){
        dis[i] = INF;
        vis[i] = false;
    }
    dis[src] = 0;
    priority_queue<int,vector<int>,cmp> que;
    que.push(src);
    while (!que.empty()) {
        int u = que.top();
        que.pop();
        vis[u] = true;
        for(int i = gph.head[u]; i ; i = gph.nxt[i]){
            int v = gph.ed[i];
//            if(vis[v] && dis[v] > dis[u] + gph.cst[i]){
//                cerr << "wtf" << endl;
//            }
            //这个问题跟dijkstra里面优先队列的工作方式有关系！
            if(vis[v] && dis[v] > dis[u] + gph.cst[i]){
                cerr << "wtf" << endl;
            }
            if(!vis[v] && dis[v] > dis[u] + gph.cst[i]){
                dis[v] = dis[u] + gph.cst[i];
                que.push(v);
            }
        }
    }
}

int dp[MAXN];
int dfs(int u,int par){
    if(dp[u]){
        return dp[u];
    }
    if(u == 2){
        return dp[2] = 1;
    }
    int ret = 0;
    for(int i = gph.head[u];i;i = gph.nxt[i]){
        int v = gph.ed[i];
        if(dis[v] < dis[u])
        ret += dfs(v,u);
    }
    return dp[u] = ret;
}

void solve(){
    dijkstra(2);
    for(int i = 1; i<= n ; i++){
        dp[i] = 0;
    }
    int res = dfs(1,0);
    printf("%d\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d",&n) != EOF && n){
        scanf(" %d",&m);
        gph.clear();
        for(int i = 1; i <= m; i++){
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            gph.addEdge(a, b, c);
            gph.addEdge(b, a, c);
        }
        solve();
    }
    
    
    return 0;
}