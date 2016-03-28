//
//  LA5031.cpp
//  playground
//
//  Created by 張正昊 on 28/3/2016.
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


const int MAXN = 220005,MAXE = 60005,MAXQ = 600005;
int n,m;

struct Node{
    int ch[2];//0:Left 1:Right
    int r,v,siz;
    void init(int nv){
        ch[0] = ch[1] = -1;
        v = nv;
        r = rand();
        siz = 1;
    }
    bool operator < (const Node &b) const{
        return r < b.r;
    }
    int cmp(int x){
        if(x == v){
            return -1;
        }
        return (x < v)?0:1;
    }
} pool[MAXN];
int tot;

int djset[MAXN];
void dj_reset(){
    for(int i = 1; i <= n; i++){
        djset[i] = i;
    }
}
int dj_find(int a){
    if(djset[a] == a) return a;
    return djset[a] = dj_find(djset[a]);
}
void dj_link(int a,int b){
    djset[dj_find(b)] = djset[dj_find(a)];
}

void init(){
    dj_reset();
    tot = 0;
}

void maintain(int u){
    pool[u].siz = 1;
    if (pool[u].ch[0] != -1) pool[u].siz += pool[pool[u].ch[0]].siz;
    if (pool[u].ch[1] != -1) pool[u].siz += pool[pool[u].ch[1]].siz;
}

void rotate(int &o,int d){
    int k = pool[o].ch[d^1];
    pool[o].ch[d^1] = pool[k].ch[d],pool[k].ch[d] = o;
    maintain(o),maintain(k);
    o = k;
}

void insert(int &u,int val){
    if (u == -1) {
        pool[u = ++tot].init(val);
    }else{
        int d = pool[u].cmp(val);
        if (d == -1) d++;
        insert(pool[u].ch[d], val);
        if(pool[pool[u].ch[d]].r > pool[u].r) rotate(u,d^1);
    }
    maintain(u);
}

void remove(int &u,int val){
    int d = pool[u].cmp(val);
    if(d == -1){
        if (pool[u].ch[0] == -1) {
            u = pool[u].ch[1];
        }else if(pool[u].ch[1] == -1){
            u = pool[u].ch[0];
        }else{
            int lc = pool[u].ch[0],rc = pool[u].ch[1];
            int d2 = (pool[lc].r > pool[rc].r)?1:0;
            rotate(u,d2);
            remove(pool[u].ch[d2],val);
        }
    }else{
        remove(pool[u].ch[d],val);
    }
    maintain(u);
}

void merge_dfs(int &rt1,int &rt2){
    if(pool[rt2].ch[0] != -1) merge_dfs(rt1,pool[rt2].ch[0]);
    if(pool[rt2].ch[1] != -1) merge_dfs(rt1,pool[rt2].ch[1]);
    insert(rt1, pool[rt2].v);
    remove(rt2, pool[rt2].v);
    rt2 = -1;
}

int kth(int rt,int k){
    if(rt == -1 ||  pool[rt].siz < k) return 0;//ISSUE IS HERE:should add rt == -1 || k <= 0 || judge!
    int lch = pool[rt].ch[0],rch = pool[rt].ch[1];
    int lsiz = 0,rsiz = 0;
    if(lch != -1) lsiz = pool[lch].siz;
    if(rch != -1) rsiz = pool[rch].siz;
    if (k == rsiz + 1) return pool[rt].v;
    else if(k <= rsiz) return kth(rch, k);
    else return kth(lch, k - rsiz - 1);
}

int val[MAXN];
struct EdgeRequest{
    int a,b;
} EREQ[MAXE];
struct Request{
    char typ;
    int arg1,arg2;//1:D arg 2:Q arg1 arg2 3:C arg1 arg2
} REQ[MAXQ];
int RTOT;

bool enable[MAXE];
int rt[MAXN];

void solve(){
    init();
    //initial clustering
    for(int i = 1; i <= m; i++) enable[i] = true;
    for(int i = 1; i <= RTOT; i++) if (REQ[i].typ == 'D') enable[REQ[i].arg1] = false;
    for(int i = 1; i <= m; i++) if(enable[i]) dj_link(EREQ[i].a, EREQ[i].b);
    for(int i = 1; i <= RTOT; i++){
        if(REQ[i].typ == 'C'){
            swap(REQ[i].arg2, val[REQ[i].arg1]);
        }
    }
    for(int i = 1; i <= n; i++) rt[i] = -1;
    for(int i = 1; i <= n; i++) {
        if(rt[dj_find(i)] == -1){
            rt[dj_find(i)] = ++tot;
            pool[rt[dj_find(i)]].init(val[i]);
        }else{
            insert(rt[dj_find(i)], val[i]);
        }
    }
    
    //Reversing Orders
    double res = 0,cnt = 0;
    for(int i = RTOT; i >= 1; i--){
        char typ = REQ[i].typ;
        int arg1 = REQ[i].arg1,arg2 = REQ[i].arg2;
        if(typ == 'D'){
            int a = EREQ[arg1].a,b = EREQ[arg1].b;
            int pa = dj_find(a),pb = dj_find(b);
            if(pa != pb){
                if(pool[rt[pa]].siz < pool[rt[pb]].siz){
                    swap(pa, pb);
                }
                djset[pb] = pa;
                merge_dfs(rt[pa], rt[pb]);
            }
            continue;
        }
        if(typ == 'Q'){
            res += kth(rt[dj_find(arg1)],arg2);
            cnt += 1;
            continue;
        }
        if(typ == 'C'){
            remove(rt[dj_find(arg1)], val[arg1]);
            insert(rt[dj_find(arg1)], arg2);
            val[arg1] = arg2;
            continue;
        }
    }
    res /= cnt;
    printf("%.6lf\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt = 0;
    while (scanf(" %d %d",&n,&m) != EOF && m+n) {
        printf("Case %d: ",++caseCnt);
        RTOT = 0;
        for(int i = 1; i<= n; i++){
            scanf(" %d",&val[i]);
        }
        for(int i = 1; i<= m; i++){
            scanf(" %d %d",&EREQ[i].a,&EREQ[i].b);
        }
        char typ;
        while (scanf(" %c",&typ) && typ != 'E') {
            int arg1,arg2;
            scanf(" %d",&arg1);
            if(typ == 'D'){
                REQ[++RTOT] = {typ,arg1,0};
            }else{
                scanf(" %d",&arg2);
                REQ[++RTOT] = {typ,arg1,arg2};
            }
        }
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time : %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    return 0;
}
