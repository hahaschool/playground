//
//  LA4292.cpp
//  playground
//
//  Created by 張正昊 on 6/3/2016.
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

int n;

int dp[122][122][10];//[usedmatch][len][lastdigit]
const int cst[10] = {6,2,5,5,4,5,6,3,7,6};

void prep(){
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < 9; i++){
        dp[cst[i]][1][i] = 1;
    }
    for(int i = 1; i <= 100; i++){
        for(int j = 1; j <= 100; j++){
            for(int k = 0; k <= 9; k++){
                for(int l = 0; l <= 9; l++){
                    dp[i+cst[l]][j+1][l] = dp[i][j][k] | dp[i+cst[l]][j+1][l];
                }
            }
        }
    }
}

stack<char> stk;
bool dfs(int rem,int dig){
    if (rem == 0 && dig == 0) {
        return true;
    }
    for(int i = 0;i <= 9; i++){
        if (dp[rem][dig][i]) {
            if (dfs(rem-cst[i], dig-1)) {
                stk.push('0'+i);
                return true;
            }
        }
    }
    return false;
}

void solvemin(){
    for(int d = 1;d <= n; d++){
        for(int i = 1;i <= 9;i++){
            if (dp[n][d][i]) {
                if (dfs(n-cst[i],d-1)) {
                    stk.push('0'+i);
                    return;
                }
            }
        }
    }
}

void solvemax(){
    if (n % 2) {
        putchar('7');
        n -= 3;
    }
    while (n) {
        putchar('1');
        n -=2;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    prep();
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    while (caseCnt-- && scanf("%d",&n) != EOF) {
        solvemin();
        while (!stk.empty()) {
            putchar(stk.top());
            stk.pop();
        }
        putchar(' ');
        solvemax();
        puts("");
    }
    return 0;
}
