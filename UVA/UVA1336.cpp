//
//  UVA1336.cpp
//  playground
//
//  Created by 張正昊 on 16/1/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

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

int n,v,x;
struct Node{
    int x,c,d;
    bool operator < (const Node& b) const{
        return x < b.x;
    }
};
vector<Node> node;

const int MAXN = 1005;
double dp[MAXN][MAXN][2];//0:l 1:r
double vis[MAXN][MAXN];
double _dsum[MAXN];

double dsum(int from,int to){
    return _dsum[to] - _dsum[from-1];
}

void solve(){
    sort(node.begin()+1, node.end());
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            dp[i][j][0] = dp[i][j][1] = 1e20;
        }
    }
    memset(_dsum, 0, sizeof(_dsum));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n ; i++){
        _dsum[i] = _dsum[i-1] + node[i].d;
    }
    
    int il = -1,ir = -1;
    for(int i = 1 ; i <= n; i++){
        if(node[i].x < x){
            il = i;
        }
        if(node[n-i+1].x > x){
            ir = n-i+1;
        }
    }
    queue<pair<int, int> > que;
    if (il != -1) {
        double dt = (double)(x - node[il].x) / (double)v;
        dp[il][il][0] = dp[il][il][1] = dt*dsum(1,n)+(double)node[il].c;
        que.push(make_pair(il, il));
    }
    if(ir != -1 && il != ir){
        double dt = (double)(node[ir].x - x) / (double)v;
        dp[ir][ir][0] = dp[ir][ir][1] = dt*dsum(1,n)+(double)node[ir].c;
        que.push(make_pair(ir, ir));
    }
    while (!que.empty()) {
        int cl = que.front().first,cr = que.front().second;
        que.pop();
        if (vis[cl][cr]) {
            continue;
        }
        vis[cl][cr] = true;
        
        if(cl-1 >= 1){
            dp[cl-1][cr][0] = min(dp[cl-1][cr][0],dp[cl][cr][0] + ((double)(node[cl].x - node[cl-1].x) / (double)v) * (double)(dsum(1, cl-1) + dsum(cr+1, n)) + (double)node[cl-1].c);
            dp[cl-1][cr][0] = min(dp[cl-1][cr][0],dp[cl][cr][1] + ((double)(node[cr].x - node[cl-1].x) / (double)v) * (double)(dsum(1, cl-1) + dsum(cr+1, n)) + (double)node[cl-1].c);
            que.push(make_pair(cl-1, cr));
        }
        if(cr+1 <= n){
            dp[cl][cr+1][1] = min(dp[cl][cr+1][1],dp[cl][cr][1] + ((double)(node[cr+1].x - node[cr].x) / (double)v) * (double)(dsum(1, cl-1) + dsum(cr+1, n)) + (double)node[cr+1].c);
            dp[cl][cr+1][1] = min(dp[cl][cr+1][1],dp[cl][cr][0] + ((double)(node[cr+1].x - node[cl].x) / (double)v) * (double)(dsum(1, cl-1) + dsum(cr+1, n)) + (double)node[cr+1].c);
            que.push(make_pair(cl, cr+1));
        }
    }
    printf("%d\n",(int)min(dp[1][n][0],dp[1][n][1]));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d %d %d",&n,&v,&x) != EOF){
        if(n == 0 && v == 0 && x == 0){
            break;
        }
        node.clear();
        node.resize(n+1);
        for(int i = 1; i <= n; i++){
            scanf(" %d %d %d",&node[i].x,&node[i].c,&node[i].d);
        }
        solve();
    }
    return 0;
}