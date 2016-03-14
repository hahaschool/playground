//
//  UVA11613.cpp
//  playground
//
//  Created by 張正昊 on 14/3/2016.
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

const int MAXN = 303,MAXE = MAXN*MAXN*MAXN;
long long INF = 0x3f3f3f3f3f3f3f3f;
int head[MAXN],ed[MAXE],nxt[MAXE],q,frm[MAXE];
long long cst[MAXE],cap[MAXE];
void clr(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void ade(int f,int t,long long cp,long long cs){
    frm[q] = f;
    cst[q] = cs;
    cap[q] = cp;
    ed[q] = t;
    nxt[q] = head[f];
    head[f] = q++;
}
void nfade(int f,int t,long long cp,long long cs){
    ade(f,t,cp,cs);
    ade(t,f,0,-cs);
}
long long dis[MAXN],aug[MAXN];
int prv[MAXN];
bool inque[MAXN];
bool SPFA(int start,int end,long long &flow,long long &cost){
    memset(dis, 0x3f, sizeof(dis));
    memset(inque, false, sizeof(inque));
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    inque[start] = true;
    aug[start] = INF;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if (cap[i] && dis[u] + cst[i] < dis[v]) {
                dis[v] = dis[u] + cst[i];
                prv[v] = i;
                aug[v] = min(aug[u],cap[i]);
                if (!inque[v]) {
                    inque[v] = true;
                    que.push(v);
                }
            }
        }
    }
    
    if (dis[end] == INF) {
        return false;
    }
    
    //Cut when meet positive cost delta
    if (dis[end] * aug[end] > 0) {
        return false;
    }
    
    flow += aug[end];
    cost += dis[end] * aug[end];
    int u = end;
    while (u != start) {
        cap[prv[u]] -= aug[end];
        cap[prv[u]^1] += aug[end];
        u = frm[prv[u]];
    }
    return true;
}


int O;
long long I,M[105],N[105],P[105],S[105],E[105];

int moid[105][2];
int n,ss,tt;

void solve(){
    n = 0;
    for (int i = 1; i <= O; i++) {
        moid[i][0] = ++n;
        moid[i][1] = ++n;
    }
    ss = ++n,tt = ++n;
    clr();
    
    for (int i = 1; i <= O; i++) {
        //Production
        nfade(ss, moid[i][0], N[i], M[i]);
        //Sale
        nfade(moid[i][1], tt, S[i], -P[i]);
        //Transform
        nfade(moid[i][0], moid[i][1], INF, 0);
        //Storage
        for (int k = 1; k <= E[i] && k+i <= O; k++) {
            nfade(moid[i][0], moid[k+i][1], INF, I*k);
        }
    }
    
    long long flow = 0,cost = 0;
    while (SPFA(ss, tt, flow, cost));
    printf("%lld\n",-cost);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %lld",&O,&I);
        printf("Case %d: ",d);
        for (int i = 1; i <= O; i++) {
            scanf(" %lld %lld %lld %lld %lld",&M[i],&N[i],&P[i],&S[i],&E[i]);
        }
        solve();
    }
    
    
    return 0;
}
