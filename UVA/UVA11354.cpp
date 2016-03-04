//
//  UVA11354.cpp
//  playground
//
//  Created by 張正昊 on 2/3/2016.
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

const int MAXN = 50005,MAXE = 200005;
int head[MAXN],nxt[MAXE],ed[MAXE],cst[MAXE],q;
int n,m;
void gph_init(){
    for(int i = 1; i <= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void gph_addedge(int from,int to,int len){
    cst[q] = len;
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

struct disjointSet{
    static const int MAXN = 50005;
    int n;
    int par[MAXN];
    void init(int _n){
        n = _n;
        for(int i = 1; i<= n; i++){
            par[i] = i;
        }
    }
    int find(int a){
        if(par[a] == a){
            return a;
        }
        return par[a] = find(par[a]);
    }
    bool check(int a,int b){
        return find(a) == find(b);
    }
    void link(int a,int b){
        int pa = find(a);
        int pb = find(b);
        par[pa] = pb;
    }
} djset;

struct Edge{
    int a,b,c;
    bool operator < (const Edge &b) const{
        return c < b.c;
    }
} edge[MAXE/2];

bool sel[MAXE/2];
void kruskal(){
    for(int i = 1; i <= m; i++){
        sel[i] = false;
    }
    djset.init(n);
    for(int i = 1; i <= m; i++){
        if (!djset.check(edge[i].a, edge[i].b)) {
            sel[i] =true;
            djset.link(edge[i].a, edge[i].b);
        }
    }
}
void buildgph(){
    gph_init();
    for(int i = 1; i<= m; i++){
        if (sel[i]) {
            gph_addedge(edge[i].a, edge[i].b, edge[i].c);
            gph_addedge(edge[i].b, edge[i].a, edge[i].c);
        }
    }
}

const int MAXLOG = 18;
int dep[MAXN];
int par[MAXN];
int parcost[MAXN];
int ancestor[MAXN][MAXLOG];
int maxcost[MAXN][MAXLOG];

void aux_dfs(int u,int fa){
    par[u] = fa;
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if (v != fa) {
            parcost[v] = cst[i];
            dep[v] = dep[u]+1;
            aux_dfs(v, u);
        }
    }
}

void binlca_preproc(){
    for(int i = 1; i <= n; i++){
        ancestor[i][0] = par[i];
        maxcost[i][0] = parcost[i];
        for (int j = 1; (1 << j) <= n; j++) {
            ancestor[i][j] = -1;
        }
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if(ancestor[i][j-1] != -1){
                int a = ancestor[i][j-1];
                ancestor[i][j] = ancestor[a][j-1];
                maxcost[i][j] = max(maxcost[i][j-1],maxcost[a][j-1]);
            }
        }
    }
}

int binlca_query_maxcost(int p,int q){
    int log = 1;
    if (dep[p] < dep[q]) {
        swap(p,q);
    }
    while ((1 << log) <= dep[p]) {
        log++;
    }
    log--;
    
    int ans = -1;
    for(int i = log; i >= 0; i--){
        if (dep[p] - (1 << i) >= dep[q]) {
            ans = max(ans,maxcost[p][i]);
            p = ancestor[p][i];
        }
    }
    if (p == q) {
        return ans;
    }
    
    for (int i = log; i >= 0; i--) {
        if (ancestor[p][i] != -1 && ancestor[p][i] != ancestor[q][i]) {
            ans = max(ans,maxcost[p][i]);
            ans = max(ans,maxcost[q][i]);
            p = ancestor[p][i];
            q = ancestor[q][i];
        }
    }
    ans = max(ans,parcost[p]);
    ans = max(ans,parcost[q]);
    return ans;
}

void solve(){
    sort(edge+1, edge+1+m);
    kruskal();
    buildgph();
    dep[1] = 0;
    aux_dfs(1,-1);
    binlca_preproc();
    int q;
    scanf(" %d",&q);
    for(int i = 1; i <= q; i++){
        int a,b;
        scanf(" %d %d",&a,&b);
        printf("%d\n",binlca_query_maxcost(a, b));
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %d %d",&n,&m) != EOF) {
        if (caseCnt) {
            puts("");
        }
        caseCnt++;
        for(int i = 1; i<= m; i++){
            scanf(" %d %d %d",&edge[i].a,&edge[i].b,&edge[i].c);
        }
        solve();
    }
    
    return 0;
}