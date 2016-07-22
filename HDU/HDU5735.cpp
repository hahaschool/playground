//
//  HDU5735.cpp
//  playground
//
//  Created by 張正昊 on 22/7/2016.
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

int op_typ;
long long op(long long a,long long b){
    if(op_typ == 1) return a&b;
    if(op_typ == 2) return a|b;
    return a^b;
}

const int MAXN = 65555,MAXE = MAXN*2;
int n;
int head[MAXN],nxt[MAXE],ed[MAXE],par[MAXN],q;
long long weight[MAXN];
void init(){
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        par[i] = -1;
    }
    q = 2;
}
void ade(int s,int t){
    ed[q] = t;
    nxt[q] = head[s];
    head[s] = q++;
}
void assign(int a,int p){
    ade(a,p);
    ade(p,a);
    par[a] = p;
}

inline long long front(long long a){
    return (a&0x000000000000ff00LL)>>8LL;
}
inline long long rear(long long a){
    return a&0x00000000000000ffLL;
}

long long dp[MAXN];
long long ds[1<<8][1<<8];
long long bak[MAXN][1<<8];//int overflow issue here
void dfs(int u,int p){
    //Maintain Current Point's DP value
    for (int j = 0; j < (1 << 8); j++) {
        if(ds[j][rear(weight[u])] != -1)
            dp[u] = max(dp[u],ds[j][rear(weight[u])] + (op(j, front(weight[u])) << 8LL));
    }
    //Backup Before Update
    memcpy(bak[u], ds[front(weight[u])], sizeof(bak[u]));
    //Update DS for child
    for (int i = 0; i < (1 << 8); i++) {
        ds[front(weight[u])][i] = max(ds[front(weight[u])][i],dp[u] + op(i,rear(weight[u])));
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = ed[i];
        if(v != p) dfs(v, u);
    }
    //Restore DS Change
    memcpy(ds[front(weight[u])], bak[u], sizeof(bak[u]));
}

const long long MODER = 1000000007;
long long f[MAXN];
void solve(){
    memset(dp, 0, sizeof(dp));
    memset(ds, -1, sizeof(ds));
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        f[i] = weight[i] + dp[i];
    }
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        res += (long long)i * f[i];
        res %= MODER;
    }
    printf("%lld\n",(res+MODER)%MODER);
}


int main(int argc, const char * argv[]){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        char buf[10];
        scanf(" %d %s",&n,buf);
        init();
        if(buf[0] == 'A') op_typ = 1;
        else if(buf[0] == 'O') op_typ = 2;
        else op_typ = 3;
        for (int i = 1; i <= n; i++) {
            scanf(" %lld",&weight[i]);
        }
        for (int i = 2; i <= n; i++) {
            int p;
            scanf(" %d",&p);
            assign(i, p);
        }
        solve();
    }
#ifndef ONLINE_JUDGE
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
