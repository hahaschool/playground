//
//  POJ2955.cpp
//  playground
//
//  Created by 張正昊 on 21/1/2016.
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

const int MAXN = 105;
char str[MAXN];
int len;
int dp[MAXN][MAXN];//dp[from][to] = maximum rectified seq len btw from and to

void solve(){
    memset(dp, 0, sizeof(dp));
    for(int i = len; i >= 1; i--){
        dp[i][i] = 0;
        for(int j = i+1; j <= len; j++){
            dp[i][j] = dp[i][j-1];
            for(int k = i; k <= j; k++){
                if ((str[k-1] == '(' && str[j-1] == ')') ||
                    (str[k-1] == '[' && str[j-1] == ']')) {
                    dp[i][j] = max(dp[i][j],dp[i][k-1] + 2 + dp[k+1][j-1]);
                }
            }
        }
    }
    printf("%d\n",dp[1][len]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %s",str) != EOF){
        if(str[0] == 'e'){
            break;
        }
        len = (int)strlen(str);
        solve();
    }
    return 0;
}
