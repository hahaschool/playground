//
//  HDU3853.cpp
//  playground
//
//  Created by Adam Chang on 2015/4/6.
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

double dp[1005][1005];
double ps[1005][1005];
double pd[1005][1005];
double pr[1005][1005];

int main(){
    int r = 0,c = 0;
    while(scanf(" %d %d",&r,&c) != EOF){
        memset(dp, 0, sizeof(dp));
        memset(ps, 0, sizeof(ps));
        memset(pd, 0, sizeof(pd));
        memset(pr, 0, sizeof(pr));
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            scanf(" %lf %lf %lf",&ps[i][j],&pr[i][j],&pd[i][j]);
        }
    }
    int i = r;
    for (int j = c-1; j >= 1; j--) {
        if (abs(1-ps[i][j]) < 0.0000000001) {
            dp[i][j] = 0;
            continue;
        }
        dp[i][j] = pr[i][j]/(1-ps[i][j])*dp[i][j+1]+pd[i][j]/(1-ps[i][j])*dp[i+1][j]+2/(1-ps[i][j]);
    }
    for (i = r-1; i >= 1; i--) {
        for (int j = c; j >= 1; j--) {
            if (abs(1-ps[i][j]) < 0.0000000001) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = pr[i][j]/(1-ps[i][j])*dp[i][j+1]+pd[i][j]/(1-ps[i][j])*dp[i+1][j]+2/(1-ps[i][j]);
        }
    }
    printf("%.3lf\n",dp[1][1]);
    }
    return 0;
}
