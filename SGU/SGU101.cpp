//
//  SGU101.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/16.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
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

using namespace std;

vector<pair<int, int> > ljb[7];//first to second id
int n = 0;

bool vis[105];
int res[105];
int now = 0;
void dfs(int currNode){
    for (int i = 0; i < ljb[currNode].size(); i++) {
        if(!vis[abs(ljb[currNode][i].second)]){
            vis[abs(ljb[currNode][i].second)] = true;
            dfs(ljb[currNode][i].first);
            now++;
            res[now] = ljb[currNode][i].second;
        }
    }
}

int main(){
    for(int i = 0;i <= 6;i++)
    ljb[i].clear();
    scanf(" %d",&n);
    int oddpnt = 0;
    for(int i = 1;i <= n;i++){
        int a = 0,b = 0;
        scanf(" %d %d",&a,&b);
        oddpnt = a;
        ljb[a].push_back(make_pair(b,i));
        ljb[b].push_back(make_pair(a,-i));
    }
    int oddcnt = 0,evencnt = 0;
    for (int i = 0; i <= 6; i++) {
            if (ljb[i].size()%2) {
                oddcnt++;
                oddpnt = i;
            }else{
                evencnt++;
            }
    }
    if (evencnt == 7 || oddcnt == 2) {
        memset(vis,0,sizeof(vis));
        memset(res, 0, sizeof(res));
        now = 0;
        dfs(oddpnt);
        if (now != n) {
            printf("No solution\n");
        }else{
            for (int i = n; i >= 1; i--) {
                if (res[i] > 0) {
                    printf("%d +\n",res[i]);
                }else{
                    printf("%d -\n",abs(res[i]));
                }
            }
            
        }
    }else{
        printf("No solution\n");
    }
    
    return 0;
}

