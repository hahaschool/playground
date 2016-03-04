//
//  HDU3507.cpp
//  playground
//
//  Created by Adam Chang on 2015/07/30.
//  Copyright © 2015年 Adam Chang. All rights reserved.
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

#define MAXN 500000 + 10

long long sum[MAXN];
long long dp[MAXN];
int que[MAXN];

long long slope_upper(int a,int b){
    return (dp[a] + sum[a] * sum[a]) - (dp[b] + sum[b] * sum[b]);
}

long long slope_lower(int a,int b){
    return 2 * (sum[a] - sum[b]);
}

int main(){
    long long n = 0, m = 0;
    while (scanf(" %lld %lld",&n,&m) != EOF) {
        int head = 0, tail = 0;
        que[tail++] = 0;
        for (int i = 1; i <= n; i++) {
            scanf(" %lld",&sum[i]);
            sum[i] += sum[i-1];
            while (head + 1 < tail && slope_upper(que[head + 1], que[head]) <= sum[i] * slope_lower(que[head + 1], que[head])) {
                head++;
            }
            dp[i] = dp[que[head]] + m + (sum[i] - sum[que[head]]) * (sum[i] - sum[que[head]]);
            while (head + 1 < tail && slope_upper(i, que[tail - 1]) * slope_lower(que[tail - 1], que[tail - 2]) <= slope_upper(que[tail - 1], que[tail - 2]) * slope_lower(i, que[tail - 1])) {
                tail--;
            }
            que[tail++] = i;
        }
        printf("%lld\n",dp[n]);
    }
    
    return 0;
}