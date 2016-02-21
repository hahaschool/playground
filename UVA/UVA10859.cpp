//
//  UVA10859.cpp
//  playground
//
//  Created by 張正昊 on 21/2/2016.
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

const int MAXN = 1005;
const int D = 2000;
int n,m;
int head[MAXN],nxt[MAXN*2],ed[MAXN*2],q;
void gph_init(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void add_edge(int from,int to){
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

int dp[MAXN][2][2];//id,parlight,curlight
int id[MAXN];
int rt[MAXN];

void dfs_aux(int u,int _id,int par){
    id[u] = _id;
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if(v != par){
            dfs_aux(v, _id, u);
        }
    }
}

void dfs_dp(int u,int par){
    dp[u][0][1] = D;
    dp[u][1][0] = 0;
    dp[u][1][1] = D;
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if (v != par) {
            dfs_dp(v, u);
            dp[u][0][1] += min(dp[v][1][0] + 1, dp[v][1][1]);
            dp[u][1][0] += dp[v][0][1] + 1;
            dp[u][1][1] += min(dp[v][1][1],dp[v][1][0] + 1);
            if (par == -1) {
                dp[u][0][0] += dp[v][0][1] + 1;
            }
        }
    }
}

void solve(){
    int idtot = 0;
    memset(id, -1 , sizeof(id));
    for(int i = 1; i <= n; i++){
        if (id[i] == -1) {
            dfs_aux(i, ++idtot, -1);
            rt[idtot] = i;
        }
    }
    int res = 0;
    for(int i = 1; i<= idtot; i++){
        dfs_dp(rt[i], -1);
        res += min(dp[rt[i]][0][1],min(dp[rt[i]][0][0],min(dp[rt[i]][1][0],dp[rt[i]][1][1])));
    }
    printf("%d %d %d\n",res/D,m-res%D,res%D);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        //For LightOJ
        //printf("Case %d: ",d);
        scanf(" %d %d",&n,&m);
        gph_init();
        for(int i = 1; i <= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            a++,b++;
            add_edge(a, b);
            add_edge(b, a);
        }
        solve();
    }
    
    return 0;
}