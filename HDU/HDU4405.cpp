//
//  HDU4405.cpp
//  playground
//
//  Created by Adam Chang on 2015/4/4.
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

int fly[100010];
double dp[100010];

int flyme(int i){
    if (fly[i]) {
        return fly[i] = flyme(fly[i]);
    }else{
        return i;
    }
    
}

int main(){
    int n = 0,m = 0;
    while (scanf(" %d %d",&n,&m)) {
        if (!(n+m)) {
            break;
        }
        memset(dp, 0, sizeof(dp));
        memset(fly, 0, sizeof(fly));
        for (int i = 1; i <= m; i++) {
            int from = 0,to = 0;
            scanf(" %d %d",&from,&to);
            fly[from] = to;
        }
        for (int i = n-1; i >= 0;i--) {
            for (int j = 1; j <= 6; j++) {
                dp[i] += dp[flyme(i+j)]/6;
            }
            dp[i]++;
        }
        printf("%.4lf\n",dp[0]);
    }
    
    return 0;
}
