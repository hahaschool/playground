//
//  HDU5788.cpp
//  playground
//
//  Created by 張正昊 on 8/8/2016.
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


using namespace std;

typedef long long LL;

const int MAXN = 100050;
int N;
int A[MAXN];
int head[MAXN],ed[MAXN*2],nxt[MAXN*2],par[MAXN],siz[MAXN],q;
void init(){
    REP_1(i, N) head[i] = 0;
    q = 2;
}
void ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}
void dfs(int u,int p){
    par[u] = p;
    siz[u] = 1;
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p){
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}

priority_queue<int> *lst[MAXN];
priority_queue<int,vector<int>,greater<int> > *rst[MAXN];

int mid[MAXN][2];//MID,MID+1

void dfs_getmid(int u,int p){
    lst[u] = new priority_queue<int>;
    rst[u] = new priority_queue<int,vector<int>,greater<int> >;
    lst[u] -> push(A[u]);
    
    if(siz[u] == 1) {
        mid[u][0] = mid[u][1] = A[u];
        return;
    }
    
    int lb = siz[u]/2;
    if(siz[u]&1) lb++;
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p){
            dfs_getmid(v, u);
            
            if(siz[v] > lst[u]->size()+rst[u]->size()){
                swap(lst[u], lst[v]);
                swap(rst[u], rst[v]);
            }
            while (!lst[v]->empty()) {
                lst[u]->push(lst[v]->top());
                lst[v]->pop();
                if(lst[u]->size() > lb){
                    rst[u]->push(lst[u]->top());
                    lst[u]->pop();
                }
            }
            delete lst[v];
            while (!rst[v]->empty()) {
                lst[u]->push(rst[v]->top());
                rst[v]->pop();
                if(lst[u]->size() > lb){
                    rst[u]->push(lst[u]->top());
                    lst[u]->pop();
                }
            }
            delete rst[v];
        }
    }
    
    //乱序合并后顺序的修复
    while (lst[u]->top() > rst[u]->top()) {
        int l = lst[u]->top(),r = rst[u]->top();
        swap(l, r);
        lst[u]->pop();
        rst[u]->pop();
        lst[u]->push(l);
        rst[u]->push(r);
    }
    
    mid[u][0] = lst[u]->top();
    mid[u][1] = rst[u]->top();
    if(p == -1){
        delete lst[u];
        delete rst[u];
    }
}

LL fenwick[2][MAXN+1];
inline int lowbit(int x){
    return x&(-x);
}
LL fenwick_sum(int id,int x){
    LL ret = 0;
    while(x>0){
        ret += fenwick[id][x];
        x -= lowbit(x);
    }
    return ret;
}
void fenwick_add(int id,int x,LL d){
    while (x <= MAXN) {
        fenwick[id][x] += d;
        x += lowbit(x);
    }
}

LL ans[MAXN];
void dfs_getans(int u,int p){
    
    fenwick_add(0, mid[u][0], mid[u][0]);
    fenwick_add(1, mid[u][0], mid[u][1]);
    
    ans[u] -= fenwick_sum(0,MAXN) - fenwick_sum(0,A[u]-1);
    ans[u] += fenwick_sum(1,MAXN) - fenwick_sum(1,A[u]-1);
    
    
    if(siz[u] == 1){
        ans[u] -= (LL)A[u];
        ans[u] += (LL)100000;
    }
    FOR_EDGE(i, u){
        int v = ed[i];
        if(v != p) dfs_getans(v, u);
    }
    
    fenwick_add(0, mid[u][0], -mid[u][0]);
    fenwick_add(1, mid[u][0], -mid[u][1]);
}



void solve(){
    dfs(1, -1);
    dfs_getmid(1, -1);
    LL tot = 0;
    REP_1(i, N) tot += mid[i][0];
    REP_1(i, N) ans[i] = tot;
    memset(fenwick, 0, sizeof(fenwick));
    dfs_getans(1, -1);
    LL res = 0;
    REP_1(i,N) res = max(ans[i],res);
    printf("%lld\n",res);
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d",&N) != EOF) {
        init();
        REP_1(i, N)
        scanf(" %d",&A[i]);
        REP_1(i, N-1){
            int a;
            scanf(" %d",&a);
            ade(i+1, a);
            ade(a, i+1);
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

/*

 9
 3 4 4 7 1 7 8 10 10
 7 5 1 1 9 3 4 1
 
 6
 3 5 5 7 1 1
 3 4 1 2 1
 
 10
 9 10 7 6 3 9 4 8 7 9
 1 9 8 6 1 10 7 1 1
 1
 1
 2
 2 1
 1
 2
 1 2
 1
*/
/*
 100058
 100021
 100065
 100000
 100002
 100001
 -----END OF OUTPUT-----
 Time Elapsed: 2MS
 Program ended with exit code: 0
 */
