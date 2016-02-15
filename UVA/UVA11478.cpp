//
//  UVA11478.cpp
//  playground
//
//  Created by 張正昊 on 4/2/2016.
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

typedef int dtype;

struct Graph{
    static const int MAXN = 505,MAXE = 2705;
    int head[MAXN],nxt[MAXE],ed[MAXE],q,from[MAXE];
    int n,m;
    dtype cst[MAXE];
    void clear(){
        for(int i = 1; i <= n; i++){
            head[i] = 0;
        }
        q = 2;
    }
    void addEdge(int _from,int to,int len){
        from[q] = _from;
        cst[q] = len;
        ed[q] = to;
        nxt[q] = head[_from];
        head[_from] = q++;
    }
} gph;

const int MAXN = 505;
bool inque[MAXN];
int dis[MAXN],quecnt[MAXN],pre[MAXN];
bool bellman_ford(){
    //returning isHaveNegativeLoop
    queue<int> que;
    memset(quecnt, 0, sizeof(quecnt));
    memset(dis, 0, sizeof(dis));
    memset(inque, false, sizeof(inque));
    for(int i = 1; i <= gph.n; i++){
        inque[i] = true;
        que.push(i);
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        inque[u] = false;
        for(int i = gph.head[u];i;i = gph.nxt[i]){
            int v = gph.ed[i];
            if(dis[v] > dis[u] + gph.cst[i]){
                dis[v] = dis[u] + gph.cst[i];
                pre[v] = u;
                if(!inque[v]){
                    que.push(v);
                    inque[v] = true;
                    if(++quecnt[v] > gph.n){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool check(int mid){
    for(int i = 2; i < gph.q; i++){
        gph.cst[i] -= mid;
    }
    bool ret = !bellman_ford();
    for(int i = 2; i < gph.q; i++){
        gph.cst[i] += mid;
    }
    return ret;
}

int ub = -1;
void solve(){
    if(check(ub+1)){printf("Infinite\n");return;}
    else if(!check(1)) {printf("No Solution\n");return;}
    int l = 1,r = ub,mid;
    while(l+1<r){
        mid = l + (r-l)/2;
        if(check(mid)){
            l = mid;
        }else{
            r = mid-1;
        }
    }
    int ans;
    if(check(r)){
        ans = r;
    }else{
        ans = l;
    }
    printf("%d\n",ans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d %d",&gph.n,&gph.m) != EOF){
        gph.clear();
        ub = 0;
        for(int i = 1; i <= gph.m; i++){
            int a,b,c;
            scanf(" %d %d %d",&a,&b,&c);
            gph.addEdge(a, b, c);
            ub = max(ub,c);
        }
        solve();
    }
    
    return 0;
}