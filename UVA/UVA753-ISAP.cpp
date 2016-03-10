//
//  UVA753.cpp
//  playground
//
//  Created by 張正昊 on 7/3/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//Network Flow ISAP Ver.

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

const int MAXN = 404,MAXE = MAXN * MAXN,INF = 0x3f3f3f3f;
int head[MAXN],ed[MAXE],nxt[MAXE],cap[MAXE],q;
int n,m;
void clr(){
    for(int i = 1; i<= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void ade(int f,int t,int c){
    cap[q] = c;
    ed[q] = t;
    nxt[q] = head[f];
    head[f] = q++;
}

int numh[MAXN],h[MAXN],curedge[MAXN],pre[MAXN];
int ISAP(int start,int end){
    int cur_flow,flow_ans = 0,u,neck = 0,tmp;
    for (int i = 1; i <= n; i++) {
        h[i] = 0;
        numh[i] = 0;
        pre[i] = -1;
        curedge[i] = head[i];
    }
    numh[0] = n;
    u = start;
    while (h[start] < n) {
        //When augment path is found previously
        if (u == end) {
            cur_flow = INF;
            for(int i = start;i != end;i = ed[curedge[i]]){
                if (cur_flow > cap[curedge[i]]) {
                    neck = i;
                    cur_flow = cap[curedge[i]];
                }
            }
            
            for (int i = start; i != end; i = ed[curedge[i]]) {
                tmp = curedge[i];
                cap[curedge[i]] -= cur_flow;
                cap[curedge[i]^1] += cur_flow;
            }
            
            flow_ans += cur_flow;
            u = neck;
        }
        
        //Find augment path
        int arc = curedge[u];
        for(;arc;arc = nxt[arc]){
            int v = ed[arc];
            if (cap[arc] && h[u] == h[v] + 1) {
                break;
            }
        }
        if (arc) {
            curedge[u] = arc;
            pre[ed[arc]] = u;
            u = ed[arc];
        }else{
            if (0 == --numh[h[u]]) {
                break;//GAP Optimization
            }
            curedge[u] = head[u];//Reset curedge Pointer
            tmp = n;
            for(int i = head[u];i;i = nxt[i]){
                int v = ed[i];
                if (cap[i]) {
                    tmp = min(tmp,h[v]);
                }
            }
            h[u] = tmp+1;
            numh[h[u]]++;
            if (u != start) {
                u = pre[u];//Back to the previoud point of u and retry augment
            }
        }
    }
    return flow_ans;
}
void nfade(int f,int t,int c){
    ade(f,t,c);
    ade(t,f,0);
}

int N,M,K;
map<string,int> shape;
int tot;
int receptacle[105],converter[105][2],device[105];

int ss,tt;
void buildgph(){
    n = tot+2;
    clr();
    ss = tot + 1,tt = tot + 2;
    for (int i = 1; i <= N; i++) {
        nfade(receptacle[i], tt, 1);
    }
    for(int i = 1; i <= M; i++){
        nfade(ss, device[i], 1);
    }
    for (int i = 1; i <= K; i++) {
        nfade(converter[i][0], converter[i][1], INF);
    }
}

void solve(){
    buildgph();
    int res = ISAP(ss, tt);
    cout << M-res << '\n';
}

int main(){
//#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r", stdin);
//#endif
    int caseCnt = 0;
    cin >> caseCnt;
    while (caseCnt-- && cin >> N) {
        tot = 0;
        shape.clear();
        for(int i = 1; i <= N; i++){
            string tmp;
            cin >> tmp;
            if (!shape.count(tmp)) {
                shape[tmp] = ++tot;
            }
            receptacle[i] = shape[tmp];
        }
        cin >> M;
        for (int i = 1; i <= M; i++) {
            string tmp;
            cin >> tmp >> tmp;
            if (!shape.count(tmp)) {
                shape[tmp] = ++tot;
            }
            device[i] = shape[tmp];
        }
        cin >> K;
        for(int i = 1; i<= K; i++){
            string tmp1,tmp2;
            cin >> tmp1 >> tmp2;
            if (!shape.count(tmp1)) {
                shape[tmp1] = ++tot;
            }
            if (!shape.count(tmp2)) {
                shape[tmp2] = ++tot;
            }
            converter[i][0] = shape[tmp1];
            converter[i][1] = shape[tmp2];
        }
        solve();
        if (caseCnt) {
            puts("");
        }
    }
    return 0;
}
