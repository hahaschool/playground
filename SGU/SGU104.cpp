//
//  SGU104.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/18.
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

int aes[105][105];
int dp[105][105][2]; // 0 is value 1 is pre

int main(){
    int f = 0,v = 0;
    scanf(" %d %d",&f,&v);
    memset(aes, 0, sizeof(aes));
    for (int i = 1; i <= f; i++) {
        for (int j = 1; j <= v; j++) {
            scanf(" %d",&aes[i][j]);
        }
    }
    memset(dp, 0xf3f3, sizeof(dp));
    for (int i = 1; i <= v; i++) {
        dp[1][i][0] = aes[1][i];
        dp[1][i][1] = 0;
    }
    for (int i = 1; i <= f; i++) {
        for (int j = 2; j <= v; j++) {
            for (int k = 1;k < j; k++) {
                if (dp[i][j][0] < dp[i-1][k][0] + aes[i][j]) {
                    dp[i][j][0] = dp[i-1][k][0] + aes[i][j];
                    dp[i][j][1] = k;
                }
            }
        }
    }
    int maxn = 0xf3f3f3f3,maxi = 0;
    for (int i = 1; i <= v; i++) {
        if (dp[f][i][0] > maxn) {
            maxn = dp[f][i][0];
            maxi = i;
        }
    }
    stack<int> curstk;
    int cur = maxi;
    while (f) {
        curstk.push(cur);
        cur = dp[f--][cur][1];
    }
    printf("%d\n",maxn);
    while (curstk.size() > 1) {
        printf("%d ",curstk.top());
        curstk.pop();
    }
    printf("%d\n",curstk.top());
    curstk.pop();
    
    return 0;
}