//
//  14-F.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/14.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//
/*
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

long long dp[100000];

int main(){
    for (int i = 1; i<= 100000; i++) {
        long long tmp = 0;
        long long base = 0;
        while (i-base > 0) {
            tmp += i-base;
            base = base*10 + 9;
        }
        dp[i] = dp[i-1] + tmp;
    }
    
    int caseCnt = 0;
    cin >> caseCnt;
    while (caseCnt--) {
        long long n = 0;
        cin >> n;
        long long pos = lower_bound(dp+1, dp+100000, n) - dp;
        pos--;
        n -= dp[pos];
        
        long long judge = 10;
        long long fact = 1;
        while (n / fact >= judge) {
            fact++;
            n += judge - 1;
            judge *= 10;
        }
        char num[1000];
        memset(num, 0, sizeof(num));
        sprintf(num, "%lld%lld",(n/fact)%10,(n/fact+1));
        cout << num[n%fact] << endl;
    }
    return 0;
    
}*/