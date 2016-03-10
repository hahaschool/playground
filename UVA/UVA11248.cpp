//
//  UVA11248.cpp
//  playground
//
//  Created by 張正昊 on 10/3/2016.
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

const int MAXN = 105,MAXE = MAXN*MAXN*4;//ISSUE3:数组开小RE
const long long INF = 0x3f3f3f3f3f3f3f3f;//ISSUE2:注意到题目中C过大，要用ll维护cap
int head[MAXN],ed[MAXE],frm[MAXE],nxt[MAXE],q;
long long cap[MAXE];
long long bakcap[MAXE];
int n;
void clr(){
    for(int i = 1;i <= n; i++){
        head[i] = 0;
    }
    q = 2;
}
void ade(int f,int t,long long c){
    frm[q] = f;
    ed[q] = t;
    cap[q] = c;
    nxt[q] = head[f];
    head[f] = q++;
}

bool vis[MAXN];
int dis[MAXN];
bool dinic_bfs(int start,int end){
    for(int i = 1; i<= n; i++){
        vis[i] = false;
    }
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    vis[start] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for(int i = head[u];i;i = nxt[i]){
            int v = ed[i];
            if (!vis[v] && cap[i]) {
                vis[v] = 1;
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return vis[end];
}

int stk[MAXE];
int stktop;
bool record;

int cur[MAXN];
long long dinic_dfs(int u,long long a,int start,int end){
    if (u == end || a == 0) {
        return a;
    }
    long long flow = 0,f;
    for(int &i = cur[u];i;i = nxt[i]){
        int v = ed[i];
        if (dis[v] == dis[u] + 1 &&
            (f = dinic_dfs(v, min(a,cap[i]), start, end)) > 0) {
            cap[i] -= f;
            cap[i^1] += f;
            if (record) {
                stk[++stktop] = i;
                stk[++stktop] = i^1;
            }
            flow += f;
            a -= f;
            if (a == 0) {
                break;
            }
        }
    }
    return flow;
}
long long dinic(int start,int end){
    record = false;
    long long flow = 0;
    while (dinic_bfs(start, end)) {
        for (int i = 1;i <= n; i++) {
            cur[i] = head[i];
        }
        flow += dinic_dfs(start, INF, start, end);
    }
    return flow;
}


int N,E;
long long C;

void nfade(int f,int t,long long c){
    ade(f,t,c);
    ade(t,f,0);
}


int cedge[MAXE];
int ctot;
vector<pair<int, int> > res;


void resume(){
    //恢复cap到刚刚跑完第一次dinic的状态
    while (stktop) {
        cap[stk[stktop]] = bakcap[stk[stktop]];
        stktop--;
    }
}

bool check(int id,long long cf){
    //临时性修改一条边的cap，在原始状态上继续dinic过程，期间记录对cap的增量修改以便撤销
    record = true;
    cap[cedge[id]] = INF;
    stk[++stktop] = cedge[id];
    long long ag = 0;
    bool ret = false;
    while (dinic_bfs(1, N)) {
        for (int i = 1;i <= n; i++) {
            cur[i] = head[i];
        }
        ag += dinic_dfs(1, INF, 1, N);
        if (ag + cf >= C) {
            ret = true;
            break;
        }
    }
    resume();
    return ret;
}

void solve(){
    long long mxf = dinic(1, N);
    if (mxf >= C) {
        puts("possible");
    }else{
        for (int i = 1; i <= q; i++) {
            bakcap[i] = cap[i];//ISSUE1:忘了备份原来cap了
        }
        ctot = 0;
        int cr = 2;
        while (cr < q) {
            if (cap[cr] == 0) {
                cedge[++ctot] = cr;
                //cout << "Cutting Edge: from " << frm[cr] << " to " << ed[cr] << endl;
            }
            cr += 2;
        }
        res.clear();
        for (int i = 1; i <= ctot; i++) {
            if (check(i,mxf)) {
                res.push_back(make_pair(frm[cedge[i]], ed[cedge[i]]));
            }
        }
        sort(res.begin(),res.end());
        if (!res.size()) {
            puts("not possible");
        }else{
            printf("possible option:");
            for(int i = 0; i< res.size();i++){
                printf("(%d,%d)",res[i].first,res[i].second);
                if (i != res.size()-1) {
                    putchar(',');
                }else{
                    putchar('\n');
                }
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    while (scanf(" %d %d %lld",&N,&E,&C) != EOF && N+E+C) {
        printf("Case %d: ",++caseCnt);
        n = N;
        clr();
        for (int i = 1; i <= E; i++) {
            int a,b;
            long long c;
            scanf(" %d %d %lld",&a,&b,&c);
            nfade(a,b,c);
        }
        solve();
    }
    
    
    return 0;
}
