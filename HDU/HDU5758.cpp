//
//  HDU5758.cpp
//  playground
//
//  Created by 張正昊 on 27/7/2016.
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

const int MAXN = 100005,MAXE = 2*MAXN;
int head[MAXN],ed[MAXE],nxt[MAXE],val[MAXE],deg[MAXN],q;
int n;
void init(){
    q = 2;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        deg[i] = 0;
    }
}
void ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
    deg[s]++;
}

int leafcnt;

int leafsiz[MAXN],res_dfs;
void dfs(int u,int par){
    leafsiz[u] = (deg[u]==1);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ed[i];
        if(v != par){
            dfs(v,u);
            leafsiz[u] += leafsiz[v];
            if(leafsiz[v]&1) val[i] = val[i^1] = 1;
            else val[i] = val[i^1] = 2;
            res_dfs += val[i];
        }
    }
}

int res_dfs2;
void dfs2(int u,int par,int cur){
    res_dfs2 = min(cur,res_dfs2);
    for (int i = head[u]; i; i=nxt[i]) {
        int v = ed[i];
        if(v != par){
            dfs2(v, u, cur + ((val[i]==1)?1:-1));
        }
    }
}

void solve(){
    leafcnt = 0;
    int lstleaf = -1;
    for (int i = 1; i <= n; i++) {
        if(deg[i] == 1){
            leafcnt++;
            lstleaf = i;
        }
    }
    res_dfs = 0;
    dfs(lstleaf,-1);
    res_dfs2 = 0;
    if(leafcnt&1)dfs2(lstleaf, -1, 0);
    
    printf("%d\n",res_dfs + res_dfs2);
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        scanf(" %d",&n);
        init();
        for (int i = 1; i <= n-1; i++) {
            int a,b;
            scanf(" %d %d",&a,&b);
            ade(a,b);
            ade(b,a);
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}