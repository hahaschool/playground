//
//  LA2957.cpp
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

const int MAXN = 5550,MAXE = 100005,INF = 0x3f3f3f3f;
int head[MAXN],ed[MAXE],nxt[MAXE],cap[MAXE],q;
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
bool vis[MAXN];
int dis[MAXN];
bool dinic_bfs(int start,int end){
    for(int i = 1; i <= n; i++){
        vis[i] = false;
    }
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    vis[start] = true;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for (int i = head[u];i;i = nxt[i]) {
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
    for (int &i = cur[u]; i; i = nxt[i]) {
        int v = ed[i];
        if (dis[u] + 1 == dis[v] &&
            (f = dinic_dfs(v, min(a,cap[i]), start, end)) > 0) {
            flow += f;
            cap[i] -= f;
            cap[i^1] += f;
            a -= f;
            if (a == 0) {
                break;//OPTIMIZATION
            }
        }
    }
    return flow;
}

int N,M,K,S,T,ss,tt;

int idx[55][555];
int eid[55][55][555];

struct Edge{
    int a,b;
} edge[202];

void addLayer(int d){
    for (int i = 1; i<= N; i++) {
        idx[i][d] = ++n;
        nfade(idx[i][d-1], idx[i][d], INF);
    }
    for(int i = 1; i<= M; i++){
        eid[edge[i].a][edge[i].b][d] = q;
        nfade(idx[edge[i].a][d-1], idx[edge[i].b][d], 1);
        eid[edge[i].b][edge[i].a][d] = q;
        nfade(idx[edge[i].b][d-1], idx[edge[i].a][d], 1);
    }
    nfade(idx[T][d], tt, INF);
}


vector<pair<int, int> > stand[55];
int tot;
vector<pair<int, int> > ans2;
void move(int f,int t,int d){
        pair<int, int> pend;
        for (vector<pair<int, int> >::iterator it = stand[f].begin(); it != stand[f].end(); it++) {
            if (it->second < d) {
                pend = *it;
                stand[f].erase(it);
                break;
            }
        }
        pend.second = d;
        stand[t].push_back(pend);
        ans2.push_back(make_pair(pend.first, t));
}

void solve(){
    n = N+2;
    ss = N+1,tt = N+2;
    clr();
    for(int i = 1; i<= n; i++){
        idx[i][0] = i;
    }
    nfade(ss, idx[S][0], K);
    nfade(idx[T][0], tt, INF);
    int day = 0;
    int mf = 0;
    while (mf < K) {
        day++;
        addLayer(day);
        while (dinic_bfs(ss, tt)) {
            for (int i = 1; i <= n; i++) {
                cur[i] = head[i];
            }
            mf += dinic_dfs(ss, INF, ss, tt);
            if (mf >= K) {
                break;
            }
        }
    }
    printf("%d\n",day);
    tot=0;
    for (int i = 1; i <= N; i++) {
        stand[i].clear();
    }
    for(int i = 1; i<= K; i++){
        stand[S].push_back(make_pair(i, 0));
    }
    for (int i = 1; i <= day; i++) {
        vector<pair<int, int> > ans;
        
        for (int j = 1; j <= M; j++) {
            if (cap[eid[edge[j].a][edge[j].b][i]^1] && cap[eid[edge[j].b][edge[j].a][i]^1]) {
                continue;
            }
            if (cap[eid[edge[j].a][edge[j].b][i]^1]) {
                ans.push_back(make_pair(edge[j].a, edge[j].b));
            }else if(cap[eid[edge[j].b][edge[j].a][i]^1]){
                ans.push_back(make_pair(edge[j].b, edge[j].a));
            }
        }
        printf("%d",(int)ans.size());
        ans2.clear();
        for (int j = 0; j < ans.size(); j++) {
            move(ans[j].first,ans[j].second,i);
        }
        sort(ans2.begin(), ans2.end());
        for(int j = 0;j < ans2.size(); j++){
            printf(" %d %d",ans2[j].first,ans2[j].second);
        }
        puts("");
    }
    
}

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    while (scanf(" %d %d %d %d %d",&N,&M,&K,&S,&T) != EOF) {
        n = 0;
        for (int i = 1; i <= M; i++) {
            scanf(" %d %d",&edge[i].a,&edge[i].b);
        }
        solve();
    }
    
    
    return 0;
}
