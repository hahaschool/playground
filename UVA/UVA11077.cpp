//
//  UVA11077.cpp
//  playground
//
//  Created by 張正昊 on 26/4/2016.
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

const int MAXN = 33;
unsigned long long dp[MAXN][MAXN];

void prepare(){
    dp[1][0] = 1;
    for (int i = 2; i <= 21; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= 21; j++) {
            dp[i][j] = dp[i-1][j] + dp[i-1][j-1] * (i-1);
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    prepare();
    int a,b;
    while (scanf(" %d %d",&a,&b) != EOF && a+b) {
        printf("%llu\n",dp[a][b]);
    }
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
