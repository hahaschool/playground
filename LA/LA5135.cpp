//
//  LA5135.cpp
//  playground
//
//  Created by 張正昊 on 22/1/2016.
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
//const int MAXN = 55,MAXE = 110;
const int MAXN = 50005,MAXE = 100005;
map<int,int> id;
int n,m;
int head[MAXN],nxt[MAXE],ed[MAXE],q;
void gph_clear(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void gph_addEdge(int from,int to){
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

vector<vector<int> > bcc;
struct Edge{
    int u,v;
};
stack<Edge> stk;
int pre[MAXN],bccid[MAXN],isCut[MAXN],dfn;
int bcc_dfs(int u,int par){
    int lowu = pre[u] = ++dfn;
    int child = 0;
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        Edge e = {u,v};
        if (!pre[v]) {
            child++;
            stk.push(e);
            int lowv = bcc_dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]){
                //articulation
                isCut[u] = true;
                bcc.push_back(vector<int>());
                while(true){
                    Edge x = stk.top();
                    stk.pop();
                    if(bccid[x.u] != (int)bcc.size()-1){
                        bccid[x.u] = (int)bcc.size()-1;
                        bcc[bccid[x.u]].push_back(x.u);
                    }
                    if(bccid[x.v] != (int)bcc.size()-1){
                        bccid[x.v] = (int)bcc.size()-1;
                        bcc[bccid[x.v]].push_back(x.v);
                    }
                    if(x.u == u && x.v == v){
                        break;
                    }
                }
            }
        }else if(pre[v] < pre[u] && v != par){
            lowu = min(lowu,pre[v]);
            stk.push(e);
        }
    }
    if(child == 1 && par < 0) isCut[u] = false;;
    return lowu;
}
void bcc_get(){
    dfn = 0;
    bcc.clear();
    for(int i = 1; i<= n; i++){
        pre[i] = 0;
        bccid[i] = -1;
        isCut[i] = false;
    }
    for(int i = 1; i<= n; i++){
        if(!pre[i]){
            bcc_dfs(i,-1);
        }
    }
}


void solve(){
    bcc_get();
    if(bcc.size() != 1){
        int ans1 = 0;
        long long ans = 1;
        for(int i = 0; i < bcc.size();i++){
            long long tmp = 0,tmparc = 0;
            for(int j = 0; j < bcc[i].size(); j++){
                if(isCut[bcc[i][j]]){
                    tmparc++;
                }else{
                    tmp++;
                }
            }
            if(tmparc == 1){
                ans1++;
                ans *= tmp;
            }
        }
        printf("%d ",ans1);
        cout << ans << endl;
    }else{
        printf("2 ");
        cout << ((long long)(bcc[0].size())*(long long)(bcc[0].size()-1))/2LL << endl;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while(scanf(" %d",&n) != EOF){
        if(n == 0){
            break;
        }
        id.clear();
        printf("Case %d: ",++caseCnt);
        gph_clear();
        m = n;
        int nn = 0;
        for(int i = 1; i<= m; i++){
            int a,b;
            scanf(" %d %d",&a,&b);
            if(!id.count(a)){
                id[a] = ++nn;
            }
            if(!id.count(b)){
                id[b] = ++nn;
            }
            gph_addEdge(id[a], id[b]);
            gph_addEdge(id[b], id[a]);
        }
        n = nn;
        solve();
    }
    return 0;
}



