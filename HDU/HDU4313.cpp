//
//  HDU4313.cpp
//  playground
//
//  Created by Adam Chang on 2015/07/29.
//  Copyright © 2015年 Adam Chang. All rights reserved.
//
/*
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

using namespace std;

static long long MAXN = 909303909303;

struct nodeType{
    vector<int> to;
    vector<int> cost;
    int color;
} vertex[100005];

void addEdge(int from,int to,int cost){
    vertex[from].to.push_back(to);
    vertex[from].cost.push_back(cost);
}

long long dp[100005][2];
void dfs(int cur, int par){
    nodeType &currNode = vertex[cur];
    for (int i = 0; i < currNode.to.size(); i++) {
        if (currNode.to[i] != par) {
            dfs(currNode.to[i], cur);
        }
    }
    if (currNode.color == 1) {
        dp[cur][0] = MAXN;
        dp[cur][1] = 0;
        for (int i = 0; i < currNode.to.size(); i++) {
            if (currNode.to[i] != par) {
                dp[cur][1] += min(dp[currNode.to[i]][0],min(dp[currNode.to[i]][0]+currNode.cost[i], dp[currNode.to[i]][1]+currNode.cost[i]));
            }
        }
    }else {
        dp[cur][0] = 0;
        dp[cur][1] = 0;
        for (int i = 0; i < currNode.to.size(); i++) {
            if (currNode.to[i] != par) {
                dp[cur][1] = min(dp[cur][0]+dp[currNode.to[i]][1], min(dp[cur][1]+dp[currNode.to[i]][0],min(dp[cur][1]+dp[currNode.to[i]][0]+currNode.cost[i], dp[cur][1]+dp[currNode.to[i]][1]+currNode.cost[i])));
                dp[cur][0] += min(dp[currNode.to[i]][0], min(dp[currNode.to[i]][0]+currNode.cost[i], dp[currNode.to[i]][1]+currNode.cost[i]));
            }
        }
    }
}

int main(){
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    while (caseCnt--) {
        int n = 0,k = 0;
        scanf(" %d %d",&n,&k);
        for (int i = 0; i < n; i++) {
            //init
            vertex[i].to.clear();
            vertex[i].cost.clear();
            vertex[i].color = 0;
        }
        for (int i = 0; i < n-1; i++) {
            int a = 0,b = 0,c = 0;
            scanf(" %d %d %d",&a,&b,&c);
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        for (int i = 0; i < k; i++) {
            int blkpt = 0;
            scanf(" %d",&blkpt);
            vertex[blkpt].color = 1;
        }
        dfs(0, -1);
        cout << min(dp[0][0], dp[0][1]) << endl;
    }
    return 0;
}
*/