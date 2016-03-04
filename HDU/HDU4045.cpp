//
//  HDU4045.cpp
//  playground
//
//  Created by Adam Chang on 2015/05/23.
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
#include <map>

using namespace std;

long long dp[1005][1005];
long long stirling2[1005][1005];
const long long MODER = 1000000007;
int n = 0,r = 0,k = 0,m = 0;

void genDP(){
    memset(dp, 0, sizeof(dp));
    long long dps[1005];
    for (int i = 1; i <= n; i++) {
        dp[i][r] = 1;
        dps[i] = i;
    }
    for (int i = r-1; i >= 1; i--) {
        for (int j = 1; j <= n && n >= j+k-1; j++) {
            dp[j][i] += dps[n] - dps[j+k-1];
            dp[j][i] %= MODER;
        }
        memset(dps, 0, sizeof(dps));
        for (int j = 1; j <= n; j++) {
            dps[j] = dps[j-1] + dp[j][i];
            dps[i] %= MODER;
        }
    }
}

void genStirling2(){
    memset(stirling2, 0, sizeof(stirling2));
    for (int i = 1; i <= 1000; i++) {
        stirling2[i][i] = 1;
        stirling2[i][1] = 1;
    }
    for (int i = 3; i <= 1000; i++) {
        for (int j = 2; j < i; j++) {
            stirling2[i][j] = stirling2[i-1][j-1] + j * stirling2[i-1][j];
            stirling2[i][j] %= MODER;
        }
    }
}

long long solve(){
    long long ret = 0;
    long long st2 = 0;
    for (int i = 1; i <= m; i++) {
        st2 += stirling2[r][i];
        st2 %= MODER;
    }
    for (int i = 1; i <= n; i++) {
        ret += dp[i][1]*st2;
        ret %= MODER;
    }
    return (ret+MODER)%MODER;
}


int main(){
    genStirling2();
    while (cin >> n >> r >> k >> m) {
        genDP();
        cout << solve() << endl;
    }
    return 0;
}
