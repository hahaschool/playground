//
//  LA4123.cpp
//  playground
//
//  Created by 張正昊 on 6/4/2016.
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

long long dp[1005][5][2];//the number of R,adjacent pairs of R,the first one being R(0) or O(1)

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    dp[1][0][1] = dp[1][0][0] = 1;
    for(int i = 2;i <= 1000; i++){
        for (int j = 0; j <= 4;j++) {
            dp[i][j][0] = dp[i-1][j][0];
            if(j) dp[i][j][0] += dp[i-1][j-1][0];
            dp[i][j][1] = dp[i-1][j][1];
            if(j) dp[i][j][1] += dp[i-1][j-1][1];
        }
    }
    int q,caseCnt = 0;
    while (scanf(" %d",&q) != EOF && q) {
        cout << "Case " << ++caseCnt << ": ";
        if (q < 4 || q & 1) cout << 0 << '\n';
        else cout << dp[(q+4)/2][3][0] + dp[(q+4)/2][4][0] + dp[(q+4)/2][4][1] << '\n';
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
