//
//  LA4287.cpp
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

const int MAXN = 20005,MAXE = 50005;
int head[MAXN],nxt[MAXE],ed[MAXE],q,ind[MAXN],outd[MAXN];
int n,m;
void gph_clear(){
    q = 2;
    for(int i = 1; i <= n; i++){
        head[i] = 0;
        ind[i] = 0;
        outd[i] = 0;
    }
}
void gph_addEdge(int from,int to){
    ind[to]++;
    outd[from]++;
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

vector<vector<int> > scc;
stack<int> stk;
int dfn,low[MAXN],pre[MAXN],sccno[MAXN];
void scc_dfs(int u){
    pre[u] = low[u] = ++dfn;
    stk.push(u);
    for(int i = head[u];i;i = nxt[i]){
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
        while(true){
            int x = stk.top();
            stk.pop();
            sccno[x] = (int)scc.size();
            scc[scc.size()-1].push_back(x);
            if(x == u){
                break;
            }
        }
    }
}
void scc_get(){
    dfn = 0;
    scc.clear();
    for(int i = 1; i<= n; i++){
        pre[i] = 0;
        sccno[i] = 0;
    }
    for(int i = 1; i<= n; i++){
        if(!pre[i]){
            scc_dfs(i);
        }
    }
}

vector<pair<int, int> > edge;

void solve(){
    scc_get();
    if(scc.size() == 1){
        puts("0");
    }else{
        gph_clear();
        for(int i = 0; i < edge.size(); i++){
            //ISSUE:缩点时，如果两个点对应同一个SCC，不要加边，也就是去掉自环，保证入度有意义
            if(sccno[edge[i].first] != sccno[edge[i].second]){
                gph_addEdge(sccno[edge[i].first], sccno[edge[i].second]);
            }
        }
        int a = 0,b = 0;
        for(int i = 1; i <= scc.size(); i++){
            if(!ind[i]){
                a++;
            }
            if(!outd[i]){
                b++;
            }
        }
        printf("%d\n",max(a,b));
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt; d++){
        scanf(" %d %d",&n,&m);
        gph_clear();
        edge.clear();
        for(int i = 1; i<= m ; i++){
            int a, b;
            scanf(" %d %d",&a,&b);
            edge.push_back(make_pair(a,b));
            gph_addEdge(a, b);
        }
        solve();
    }
    return 0;
}



