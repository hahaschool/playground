//
//  UVA13015.cpp
//  playground
//
//  Created by 張正昊 on 30/8/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

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

const int MAXN = 5005,MAXE = 40005;
int head[MAXN],ed[MAXE],nxt[MAXE],q;
int rev_head[MAXN],rev_ed[MAXE],rev_nxt[MAXE],rev_q;
int n,m;
void init(){
    q = 2;
    rev_q = 2;
    REP_1(i, n){
        head[i] = rev_head[i] = 0;
    }
}
void ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}
void rev_ade(int s,int t){
    rev_ed[rev_q] = t;
    rev_nxt[rev_q] = rev_head[s];
    rev_head[s] = rev_q++;
}

int A,B;

int dp[MAXN];
bool vis[MAXN];
void dfs(int u,int id){
    dp[id]++;
    vis[u] = true;
    FOR_EDGE(i, u){
        int v = ed[i];
        if(!vis[v]) dfs(v,id);
    }
}

int ret_del;
void del(int u){
    ret_del--;
    vis[u] = true;
    for(int i = rev_head[u];i;i = rev_nxt[i]){
        int v = rev_ed[i];
        if(!vis[v]) del(v);
    }
}

int cnt[MAXN];

void solve(){
    memset(dp, 0, sizeof(dp));
    REP_1(i, n){
        memset(vis, 0, sizeof(vis));
        dfs(i,i);
    }
    
    int resa = 0,resb = 0;
    REP_1(i, n){
        ret_del = n;
        memset(vis, 0, sizeof(vis));
        del(i);
        if(ret_del < A){
            resa++;
        }
        if(ret_del < B){
            resb++;
        }
    }
    
    int res = 0;
    REP_1(i, n){
        if(dp[i] > B) res++;
    }
    printf("%d\n%d\n%d\n",resa,resb,res);
}

int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    
    while (scanf(" %d %d %d %d",&A,&B,&n,&m) != EOF) {
        init();
        REP_1(i, m){
            ADHOC_SCANINT(a);ADHOC_SCANINT(b);
            a++,b++;
            ade(b, a);
            rev_ade(a,b);
        }
        solve();
    }
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
