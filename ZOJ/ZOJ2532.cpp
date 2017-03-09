//
//  ZOJ2532.cpp
//  AnotherPlayground
//
//  Created by 張正昊 on 13/02/2017.
//  Copyright © 2017 hahaschool. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
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
#include <functional>
#include <numeric>
#include <bitset>


#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_R(i,t) for(int i = t-1;i >= 0; i--)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define REP_1R(i,t) for(int i = t;i >= 1; i--)
#define REP_ST(i,s,t) for(int i = s;i <= t; i++)
#define REP_STR(i,s,t) for(int i = s;i >= t; i--)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);
#define ADHOC_SCANCHAR(name) int name;scanf(" %c",&name);

using namespace std;

#ifdef LOCAL_DEBUG
const int MAXN = 105, MAXE = 105;
#endif
#ifndef LOCAL_DEBUG
const int MAXN = 105, MAXE = 8005;
#endif

const int INF = 1000000007;
int head[MAXN],ed[MAXE],nxt[MAXE],n,q;
int cap[MAXE],flw[MAXE],from[MAXE],id[MAXE];
void gph_clr(){
    for(int i = 1;i <= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void gph_ade(int u,int v,int c,int f,int d){
    cap[q] = c;
    flw[q] = f;
    ed[q] = v;
    id[q] = d;
    from[q] = u;
    nxt[q] = head[u];
    head[u] = q++;
}
void nf_ade(int u,int v,int c,int d){
    gph_ade(u,v,c,0,d);
    gph_ade(v,u,0,0,d);
}

bool vis[MAXN];
int cur[MAXN],dis[MAXN],ss,tt;
bool dinic_bfs(){
    queue<int> que;
    for(int i = 1;i <= n; i++){
        vis[i] = false;
    }
    que.push(ss);
    dis[ss] = 0;
    vis[ss] = true;
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int i = head[u]; i;i = nxt[i]){
            int v = ed[i];
            if(!vis[v] && flw[i] < cap[i]){
                vis[v] = true;
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return vis[tt];
}
int dinic_dfs(int u,int a){
    if(u == tt || a == 0) return a;
    int flow = 0,f;
    for(int &i = cur[u];i;i = nxt[i]){
        int v = ed[i];
        if(dis[v] == dis[u] + 1 && (f = dinic_dfs(v, min(a, cap[i] - flw[i]))) > 0){
            a -= f;
            flw[i] += f;
            flw[i^1] -= f;
            flow += f;
            if(a == 0) break;
        }
    }
    return flow;
}
int dinic(){
    int flow = 0;
    while(dinic_bfs()){
        for(int i = 1;i <= n; i++){
            cur[i] = head[i];
        }
        flow += dinic_dfs(ss, INF);
    }
    return flow;
}

int N,M,L;
int U[MAXE],V[MAXE],W[MAXE];


void buildgph(){
    n = N+M+2;
    gph_clr();
    ss = n - 1, tt = n;
    for(int i = 1;i <= N; i++){
        nf_ade(ss, i, INF, -1);
    }
    for(int i = 1; i <= L; i++){
        int u = (U[i]==0)?tt:U[i];
        int v = (V[i]==0)?tt:V[i];
        nf_ade(u, v, W[i], i);
    }
}

bool src[MAXN],dst[MAXN];
void dfs_fwd(int u){
    src[u] = true;
    for(int i = head[u]; i;i = nxt[i]){
        int v = ed[i];
        if(!src[v] && flw[i] < cap[i]){
            dfs_fwd(v);
        }
    }
}
void dfs_rev(int u){
    dst[u] = true;
    for(int i = head[u]; i; i = nxt[i]){
        int v = ed[i];
        if(!dst[v] && flw[i^1] < cap[i^1]){
            dfs_rev(v);
        }
    }
}

vector<int> res;
void solve(){
    buildgph();
    dinic();
    for(int i = 1;i <= n; i++){
        src[i] = dst[i] = false;
    }
    dfs_fwd(ss);
    dfs_rev(tt);
    res.clear();
    for(int i = 2;i < q; i += 2){
        if(flw[i] == cap[i] && src[from[i]] && dst[ed[i]]){
            res.push_back(id[i]);
        }
    }
    for(int i = 0;i < res.size(); i++){
        if(i) putchar(' ');
        printf("%d",res[i]);
    }
    puts("");
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.txt", "r", stdin);
    freopen("output.txt","w",stdout);
    clock_t clk = clock();
#endif
    
    while(scanf(" %d %d %d",&N,&M,&L) != EOF){
        if(N == 0 && M == 0 && L == 0){
            break;
        }
        for(int i = 1;i <= L; i++){
            scanf(" %d %d %d",&U[i], &V[i], &W[i]);
        }
        solve();
    }
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    

    
    return 0;
}
