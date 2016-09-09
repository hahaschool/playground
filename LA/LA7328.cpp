//
//  LA7328.cpp
//  playground
//
//  Created by 張正昊 on 4/9/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>
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
#include <functional>
#include <numeric>
#include <bitset>

#define REP(i,t) for(int i = 0;i < t; i++)
#define REP_1(i,t) for(int i = 1;i <= t; i++)
#define CASE_LOOP int ___;scanf(" %d",&___);for(int __ = 1; __ <= ___; __++)
#define FOR_EDGE(i,u) for (int i = head[u]; i; i = nxt[i])
#define ADHOC_CIN(typ,name) typ name;cin >> name;
#define ADHOC_SCANINT(name) int name;scanf(" %d",&name);


using namespace std;

typedef long long LL;

const int MAXN = 300005,MAXE = MAXN;
int n,m,q;
struct Edge{
    int u,v,c;
    bool operator < (const Edge &b) const{
        return c > b.c;
    }
} edge[MAXE];
struct Query{
    int id,val;
    int v,e;
    bool operator < (const Query &b) const{
        return val > b.val;
    }
    bool operator > (const Query &b) const{
        return b.id > id;
    }
} query[MAXN];

int dj_par[MAXN*2];
int deg[MAXN];
int deg2_cnt[MAXN],deg0_cnt[MAXN],cnt[MAXN],cur_m;
int deg0_sum = n,deg2_sum = 0,cycle_cnt = 0;
void dj_init(){
    REP_1(i, n) {
        dj_par[i] = i;
        dj_par[i+n] = i;
        deg2_cnt[i] = 0;
        deg0_cnt[i] = 1;
        cnt[i] = 1;
        deg[i] = 0;
    }
    cur_m = 0;
    deg0_sum = n,deg2_sum = 0,cycle_cnt = 0;;
}
int dj_find(int a){
    if(dj_par[a] == a) return a;
    return dj_par[a] = dj_find(dj_par[a]);
}


inline void inc_deg(int u){
    if(!deg[u]) deg0_cnt[dj_find(u+n)]--;
    else if(deg[u] == 1) deg2_cnt[dj_find(u+n)]++;
    else if(deg[u] == 2) deg2_cnt[dj_find(u+n)]--;
    deg[u]++;
}
void ade(int u,int v){
    int pa = dj_find(u+n),pb = dj_find(v+n);
    if(cnt[pa] > 1 && deg2_cnt[pa] == cnt[pa]) cycle_cnt--;
    if(pa != pb && cnt[pb] > 1 &&deg2_cnt[pb] == cnt[pb]) cycle_cnt--;
    deg0_sum -= deg0_cnt[pa];
    if(pa != pb) deg0_sum -= deg0_cnt[pb];
    deg2_sum -= deg2_cnt[pa];
    if(pa != pb) deg2_sum -= deg2_cnt[pb];
    inc_deg(u);inc_deg(v);
    
    if(pa != pb){
        cnt[pa] += cnt[pb],cnt[pb] = 0;
        deg2_cnt[pa] += deg2_cnt[pb],deg2_cnt[pb] = 0;
        deg0_cnt[pa] += deg0_cnt[pb],deg0_cnt[pb] = 0;
        dj_par[pb] = pa;
    }
    cur_m++;
    deg0_sum += deg0_cnt[pa];
    if(pa != pb) deg0_sum += deg0_cnt[pb];
    deg2_sum += deg2_cnt[pa];
    if(pa != pb) deg2_sum += deg2_cnt[pb];
    if(cnt[pa] > 1 && deg2_cnt[pa] == cnt[pa]) cycle_cnt++;
    if(pa != pb && cnt[pb] > 1 &&deg2_cnt[pb] == cnt[pb]) cycle_cnt++;
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d",&n,&m) != EOF) {
        REP_1(i, m){
            ADHOC_SCANINT(a);
            ADHOC_SCANINT(b);
            ADHOC_SCANINT(p);
            edge[i] = {a,b,p};
        }
        sort(edge+1, edge+1+m);
        
        scanf(" %d",&q);
        REP_1(i, q){
            ADHOC_SCANINT(a);
            query[i] = {i,a,0,0};
        }
        sort(query+1, query+1+q);
        
        dj_init();
        int cur = 1;
        REP_1(i, m){
            while(cur <= q && query[cur].val > edge[i].c){
                query[cur].v = n - deg0_sum - deg2_sum + cycle_cnt;
                query[cur].e = cur_m - deg2_sum + cycle_cnt;
                cur++;
            }
            ade(edge[i].u,edge[i].v);
        }
        while(cur <= q){
            query[cur].v = n - deg0_sum - deg2_sum + cycle_cnt;
            query[cur].e = m - deg2_sum + cycle_cnt;
            cur++;
        }
        sort(query+1, query+1+q, greater<Query>());
        REP_1(i, q){
            printf("%d %d\n",query[i].v,query[i].e);
        }
    }
    
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
