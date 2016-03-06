//
//  LA6606.cpp
//  playground
//
//  Created by 張正昊 on 6/3/2016.
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

const int MAXN = 105;
struct Segment{
    int a,b;
} seg[MAXN];
int n;

int head[MAXN],ed[MAXN],nxt[MAXN],q;
void clr(){
    memset(head, 0, sizeof(head));
    q = 2;
}
void addEdge(int from,int to){
    ed[q] = to;
    nxt[q] = head[from];
    head[from] = q++;
}

int dp[MAXN];
void dfs(int u,int par){
    for(int i = head[u];i;i = nxt[i]){
        int v = ed[i];
        if (v == par) {
            continue;
        }
        dp[v] = max(dp[u]+1,dp[v]);
        dfs(v, u);
    }
}

void solve(){
    clr();
    for(int i = 1; i<= n; i++){
        for(int j = 1; j <= n; j++){
            if(i != j && seg[i].b <= seg[j].a){
                addEdge(i, j);
            }
        }
    }
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i<= n; i++){
        dfs(i, -1);
    }
    int res = 0;
    for(int i = 1;i <= n; i++){
        res = max(res,dp[i]);
    }
    printf("%d\n",res+1);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        int a,b;
        n = 0;
        while (scanf(" %d %d",&a,&b) != EOF) {
            if (!a && !b) {
                break;
            }
            seg[++n].a = a;
            seg[n].b = b;
        }
        solve();
    }
    return 0;
}
