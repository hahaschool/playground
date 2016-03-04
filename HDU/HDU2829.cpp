//
//  HDU2829.cpp
//  playground
//
//  Created by Adam Chang on 2015/08/01.
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

const long long maxn = 1010;
long long n, m;
long long a[maxn], sum[maxn], sumul[maxn];
long long dp[2][maxn];
long long que[maxn], head, tail;

long long slope_upper(long long l, long long b, long long a)
{
    return (dp[l%2][a] - sumul[a] + sum[a] * sum[a]) - (dp[l%2][b] - sumul[b] + sum[b] * sum[b]);
}

long long slope_lower(long long b, long long a)
{
    return sum[a] - sum[b];
}

int main()

{
    //freopen("testdata.hdub", "r", stdin);
    while (scanf("%lld%lld", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;
        sum[0] = 0;
        sumul[0] = 0;
        for (long long i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            sum[i] = sum[i-1] + a[i];
            sumul[i] = sumul[i-1] + sum[i-1] * a[i];
            dp[0][i] = sumul[i];
        }
        for (long long i = 1; i <= m; ++i) {
            head = tail = 0;
            que[tail++] = i;
            for (long long j = i+1; j <= n; ++j) {
                while (head + 1 < tail && slope_upper(i-1, que[head], que[head+1]) <= sum[j] * slope_lower(que[head], que[head+1])) {
                    head++;
                }
                dp[i%2][j] = dp[(i-1)%2][que[head]] + sumul[j] - sumul[que[head]] - sum[que[head]] * (sum[j] - sum[que[head]]);
                while (head + 1 < tail && slope_upper(i - 1, que[tail-2], que[tail-1]) * slope_lower(que[tail-1], j) >= slope_lower(que[tail-2], que[tail-1]) * slope_upper(i - 1, que[tail-1], j)) {
                    tail--;
                }
                que[tail++] = j;
            }
        }
        printf("%lld\n", dp[m%2][n]);
    }
    return 0;
}