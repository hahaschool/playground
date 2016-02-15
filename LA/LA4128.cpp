//
//  LA4128.cpp
//  playground
//
//  Created by 張正昊 on 5/2/2016.
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

const int MAXN = 1005,MAXE = 1000005;
int n,m;
struct Edge{
    int u,v;
    double c;
    bool operator < (const Edge &b) const{
        return c < b.c;
    }
} edge[MAXE];
struct Node{
    double x,y;
} node[MAXN];

double calcdis(int from,int to){
    return sqrt(((node[from].x-node[to].x)*(node[from].x-node[to].x)+(node[from].y-node[to].y)*(node[from].y-node[to].y)));
}

struct DisjointSet{
    static const int MAXN = 1005;
    int par[MAXN];
    int n;
    void init(int _n){
        n = _n;
        for(int i = 1; i<= n ; i++){
            par[i] = i;
        }
    }
    int find(int a){
        if(par[a] == a){
            return a;
        }
        return par[a] = find(par[a]);
    }
    void link(int a,int b){
        int pa = find(a);
        int pb = find(b);
        par[pa] = pb;
    }
    bool check(int a,int b){
        return find(a) == find(b);
    }
} djset;

double mst_val;
bool mst_sel[MAXE];
void kruskal(){
    djset.init(n);
    sort(edge+1, edge+1+m);
    mst_val = 0;
    for(int i = 1; i <= m; i++){
        mst_sel[i] = false;
        if(djset.check(edge[i].u, edge[i].v)){
            continue;
        }
        djset.link(edge[i].u, edge[i].v);
        mst_sel[i] = true;
        mst_val += edge[i].c;
    }
}

void buildEdge(){
    m = 0;
    for(int i = 1;i <= n; i++){
        for(int j = i+1; j <= n; j++){
            edge[++m].u = i;
            edge[m].v = j;
            edge[m].c = calcdis(i, j);
        }
    }
}

int head[MAXN],nxt[MAXN*2],ed[MAXN*2],q;
double cst[MAXN*2];
void gph_clear(){
    for(int i = 1; i<= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void gph_addEdge(int _from,int _to,double _len){
    ed[q] = _to;
    cst[q] = _len;
    nxt[q] = head[_from];
    head[_from] = q++;
}
void buildGraph(){
    gph_clear();
    for(int i = 1; i <= m; i++){
        if(mst_sel[i]){
            gph_addEdge(edge[i].u,edge[i].v,edge[i].c);
            gph_addEdge(edge[i].v,edge[i].u,edge[i].c);
        }
    }
}

double mxel[MAXN][MAXN];
void dfs(int rt,int u = -1,double cm = -1,int par = -1){
    if(u == -1){
        dfs(rt,rt,-1,-1);
        return;
    }
    mxel[rt][u] = cm;
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if(v != par){
            dfs(rt,v,max(cm,cst[i]),u);
        }
    }
}
void calcMxel(){
    for(int i = 1; i <= n; i++){
        dfs(i);
    }
}

double people[MAXN];
void solve(){
    buildEdge();
    kruskal();
    buildGraph();
    calcMxel();
    double res = -1;
    for(int i = 1; i<= n; i++){
        for(int j = i+1; j<=n; j++){
            res = max(res,(people[i]+people[j])/(double)(mst_val-mxel[i][j]));
        }
    }
    printf("%.2lf\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt; d++){
        scanf(" %d",&n);
        for(int i = 1; i<= n; i++){
            scanf(" %lf %lf %lf",&node[i].x,&node[i].y,&people[i]);
        }
        solve();
    }
    return 0;
}