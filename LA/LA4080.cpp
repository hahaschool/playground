//
//  LA4080.cpp
//  playground
//
//  Created by 張正昊 on 30/1/2016.
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

const int MAXN = 105,MAXE = 4005;
int head[MAXN],nxt[MAXE],ed[MAXE],par[MAXN],pare[MAXN];
long long cst[MAXE];
int n,m,q;
long long l;
void gph_clear(){
    q = 2;
    for(int i = 1; i<= n; i++){
        head[i] = 0;
        par[i] = i;
        pare[i] = -1;
    }
}
void gph_addEdge(int from,int to,long long len){
    ed[q] = to;
    nxt[q] = head[from];
    cst[q] = len;
    head[from] = q++;
}

struct State{
    int i;
    long long dis;
    State(int _i,long long _dis){
        i = _i,dis = _dis;
    }
    State(){
        
    };
    bool operator < (const State & b) const{
        return dis > b.dis;
    }
};
priority_queue<State> que;
long long dis[MAXN];
const long long INF = 0x3f3f3f3f3f3f3f3f;

void dijkstra(int rt,int del){
    for(int i = 1; i<= n ; i++){
        dis[i] = INF;
        if(del == -1){
            par[i] = i;
            pare[i] = -1;
        }
    }
    dis[rt] = 0;
    que.push(State(rt,0));
    while(!que.empty()){
        int cur = que.top().i;
        que.pop();
        for(int i = head[cur];i;i = nxt[i]){
            int v = ed[i];
            if((del == -1 ||
                (i != del && i != (del^1)))&&
               dis[v] > dis[cur] + cst[i]){
                dis[v] = dis[cur] + cst[i];
                if(del == -1){
                    par[v] = cur;
                    pare[v] = i;
                }
                que.push(State(v,dis[v]));
            }
        }
    }
    
}

long long calc(){
    long long ret = 0;
    for(int i = 1; i <= n; i++){
        if (dis[i] == INF) {
            ret += l;
        }else{
            ret += dis[i];
        }
    }
    return ret;
}
long long cpart[MAXN];
bool used[MAXN][MAXE];
bool sel[MAXE];
void solve(){
    memset(used, false, sizeof(used));
    memset(sel, false, sizeof(sel));
    long long c = 0;
    for(int i = 1;i <= n;i++){
        dijkstra(i,-1);
        cpart[i] = calc();
        c += cpart[i];
        for(int j = 1;j <= n; j++){
            if(pare[j] != -1){
                used[i][pare[j]] = used[i][pare[i]^1] = true;
                sel[pare[j]] = sel[pare[j]^1] = true;
            }
        }
    }
    long long cp = -1;
    for(int i = 2; i < q; i++){
        if(sel[i]){
            long long np = 0;
            for(int k = 1; k <= n; k++){
                if(used[k][i] || used[k][i^1]){
                    dijkstra(k, i);
                    np += calc();
                }else{
                    np += cpart[k];
                }
            }
            cp = max(cp,np);
        }
    }
    printf("%lld %lld\n",c,cp);
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d %d %lld",&n,&m,&l) != EOF){
        gph_clear();
        for(int i = 1; i <= m ; i++){
            int a,b;
            long long c;
            scanf("%d %d %lld",&a,&b,&c);
            gph_addEdge(a,b,c);
            gph_addEdge(b,a,c);
        }
        solve();
    }
    return 0;
}
