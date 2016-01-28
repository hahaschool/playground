//
//  UVA11324.cpp
//  playground
//
//  Created by 張正昊 on 27/1/2016.
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

const int MAXN = 1005,MAXE = 50005;
int head[MAXN],nxt[MAXE],ed[MAXE],q;
int n,m;
void gph_clear(){
    q = 2;
    for(int i = 1; i<= n; i++){
        head[i] = 0;
    }
}
void gph_addEdge(int from,int to){
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

vector<vector<int> > scc;
stack<int> stk;
int sccno[MAXN],pre[MAXN],low[MAXN],dfn,scccnt;
void scc_dfs(int u){
    pre[u] = low[u] = ++dfn;
    stk.push(u);
    for(int i = head[u];i ;i = nxt[i]){
        int v = ed[i];
        if(!pre[v]){
            scc_dfs(v);
            low[u] = min(low[u],low[v]);
        }else if(!sccno[v]){
            low[u] = min(low[u],pre[v]);
        }
    }
    if(low[u] == pre[u]){
        scc.push_back(vector<int>());
        scccnt++;
        while(true){
            int x = stk.top();
            stk.pop();
            sccno[x] = scccnt;
            scc[scccnt].push_back(x);
            if(x == u){
                break;
            }
        }
    }
}
void scc_get(){
    scc.clear();
    scccnt = 0;
    scc.push_back(vector<int>());
    for(int i = 1; i<= n; i++){
        sccno[i] = 0;
        pre[i] = 0;
    }
    dfn = 0;
    for(int i = 1; i <= n; i++){
        if(!pre[i]){
            scc_dfs(i);
        }
    }
}

bool mat[MAXN][MAXN];
int dp[MAXN];
bool vis[MAXN];
void dfs(int u){
    if(vis[u]) return;
    vis[u] = true;
    dp[u] = (int)scc[u].size();
    int mx = 0;
    for(int i = 1; i <= scccnt ; i++){
        if(mat[u][i]){
            if(!vis[i]){
                dfs(i);
            }
            mx = max(mx,dp[i]);
        }
    }
    dp[u] += mx;
}


void solve(){
    scc_get();
    memset(mat, 0, sizeof(mat));
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i<= n; i++){
        for(int j = head[i];j;j = nxt[j]){
            int u = sccno[i];
            int v = sccno[ed[j]];
            if(u != v){
                mat[u][v] = true;
            }
        }
    }
    for(int i = 1; i <= scccnt; i++){
        dfs(i);
    }
    int res = 0;
    for(int i = 1;i <= scccnt; i++){
        res = max(res,dp[i]);
    }
    printf("%d\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        scanf(" %d %d",&n,&m);
        gph_clear();
        for(int i = 1; i<= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            gph_addEdge(a, b);
        }
        solve();
    }
    return 0;
}

