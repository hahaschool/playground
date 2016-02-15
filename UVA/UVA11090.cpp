//
//  UVA11090.cpp
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

const int MAXN = 55,MAXE = 555;
int head[MAXN],nxt[MAXE],ed[MAXE],q;
double cst[MAXE];
int n,m;
void gph_clear(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void gph_addEdge(int from,int to,double _cst){
    cst[q] = _cst;
    ed[q] = to;
    nxt[q] = head[from];
    head[from] =  q++;
}

bool inque[MAXN];
double dis[MAXN];
int pre[MAXN],quecnt[MAXN];
bool bellman_ford(){
    //returning isHavingNegativeCycle
    queue<int> que;
    memset(inque, false, sizeof(inque));
    memset(quecnt, 0, sizeof(quecnt));
    for(int i = 1; i <= n; i++){
        dis[i] = 0;
        inque[i] = true;
        que.push(i);
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        inque[u] = false;
        for(int i = head[u];i;i = nxt[i]){
            int v = ed[i];
            if(dis[v] > dis[u] + cst[i]){
                dis[v] = dis[u] + cst[i];
                pre[v] = i;
                if(!inque[v]){
                    que.push(v);
                    inque[v] = true;
                    if(++quecnt[v] > n){
                        //WARNING: this interrupts the algo.
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool check(double mid){
    for(int i = 2; i < q; i++){
        cst[i] -= mid;
    }
    bool ret = bellman_ford();
    for(int i = 2; i < q; i++){
        cst[i] += mid;
    }
    return ret;
}

void solve(){
    double l = 0,r = 1e9,EPS = 1e-4,mid;
    while(abs(l-r) > EPS){
        mid = (l+r)/2;
        if(check(mid)){
            r = mid;
        }else{
            l = mid;
        }
    }
    
    if(mid > 1e8){
        puts("No cycle found.");
        return;
    }
    printf("%.2lf\n",mid);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        printf("Case #%d: ",d);
        scanf(" %d %d",&n,&m);
        gph_clear();
        for(int i = 1; i<= m; i++){
            int a,b;
            double c;
            scanf(" %d %d %lf",&a,&b,&c);
            gph_addEdge(a, b, c);
        }
        solve();
    }
    
    return 0;
}