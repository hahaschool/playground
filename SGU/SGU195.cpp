//
//  SGU195.cpp
//  playground
//
//  Created by Adam Chang on 2015/07/29.
//  Copyright © 2015年 Adam Chang. All rights reserved.
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

using namespace std;

struct nodeType{
    vector<int> to;
    int select;
} vertex[500005];

void addEdge(int from,int to){
    vertex[from].to.push_back(to);
}

int dp[500005][2];
void dfs(int cur){
    nodeType &currNode = vertex[cur];
    for (int i = 0; i < currNode.to.size(); i++) {
        dfs(currNode.to[i]);
    }
    for (int i = 0; i < currNode.to.size(); i++) {
        if (dp[cur][0]+dp[currNode.to[i]][0]+1>= max(dp[cur][1]+dp[currNode.to[i]][1],dp[cur][1]+dp[currNode.to[i]][0])) {
            currNode.select = currNode.to[i];
        }
        dp[cur][1] = max(dp[cur][0]+dp[currNode.to[i]][0]+1, max(dp[cur][1]+dp[currNode.to[i]][1],dp[cur][1]+dp[currNode.to[i]][0]));
        dp[cur][0] = max(dp[cur][0]+dp[currNode.to[i]][1],dp[cur][0]+dp[currNode.to[i]][0]);
    }
}

vector<int> ans;
void dfs_getans(int cur){
    nodeType &currNode = vertex[cur];
    if (dp[cur][0] >= dp[cur][1]) {
        for (int i = 0; i < currNode.to.size(); i++) {
            dfs_getans(currNode.to[i]);
        }
    }else{
        if (currNode.select) {
            ans.push_back(currNode.select);
        }
        for (int i = 0; i < currNode.to.size(); i++) {
            dfs_getans(currNode.to[i]);
        }
    }
}

int main(){
    int n = 0;
    scanf(" %d",&n);
    for (int i = 1; i <= n; i++) {
        vertex[i].to.clear();
        vertex[i].select = 0;
        dp[i][0] = dp[i][1] = 0;
    }
    ans.clear();
    for (int i = 2; i <= n; i++) {
        int boss = 0;
        scanf(" %d",&boss);
        addEdge(boss,i);
    }
    dfs(1);
    dfs_getans(1);
    sort(ans.begin(), ans.end());
    cerr << dp[1][0] << " " << dp[1][1] << endl;
    printf("%d\n",(int)ans.size()*1000);
    if (ans.size()) {
        for (int i = 0; i < (int)ans.size()-1; i++) {
            printf("%d ",ans[i]);
        }
        printf("%d\n",ans[ans.size()-1]);
    }
    return 0;
}