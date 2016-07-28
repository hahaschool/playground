//
//  CF686D.cpp
//  playground
//
//  Created by 張正昊 on 25/7/2016.
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

const int MAXN = 300005, MAXE = 600005;
int n,q;
int head[MAXN],ed[MAXE],nxt[MAXE],par[MAXN],qq;
void init(){
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
    qq = 2;
}
void ade(int s,int t){
    ed[qq] = t;
    nxt[qq] = head[s];
    head[s] = qq++;
}
int sz[MAXN],centroid[MAXN];
void dfs(int u,int p){
    par[u] = p;
    centroid[u] = u;
    sz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ed[i];
        if(v != p){
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ed[i];
        if(v != p && sz[v] >= sz[u]/2){
            centroid[u] = centroid[v];
        }
    }
    while (centroid[u] != u) {
        if(sz[u] - sz[centroid[u]] > sz[u]/2){
            centroid[u] = par[centroid[u]];
        }else break;
    }
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    scanf(" %d %d",&n,&q);
    init();
    for (int i = 2; i <= n; i++) {
        int a;
        scanf(" %d",&a);
        ade(i,a);
        ade(a,i);
    }
    dfs(1, -1);
    for (int i = 1; i <= q; i++) {
        int a;
        scanf(" %d",&a);
        printf("%d\n",centroid[a]);
    }
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
