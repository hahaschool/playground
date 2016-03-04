//
//  HDU3669.cpp
//  playground
//
//  Created by Adam Chang on 2015/08/02.
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

vector<pair<long long, long long> > tmp_block;
vector<pair<long long, long long> > block;
bool cmp(pair<long long, long long> a,pair<long long, long long> b){
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second > b.second;
}
const int maxn = 50005;
const long long maxll = 0x3f3f3f3f3f3f3f3f;
long long dp[2][maxn];
int que[maxn];
int head = 0,tail = 0;

long long slope_upper(int t,int a,int b){
    return dp[(t-1)%2][a] - dp[(t-1)%2][b];
}

long long slope_lower(int a,int b){
    return block[b].second - block[a].second;
}

long long get_dp(int t,int i,int h){
    return dp[(t-1)%2][que[h]] + block[i-1].first * block[que[h]].second;
}
int main(){
    long long n = 0,k = 0;
    while (scanf(" %lld %lld",&n,&k) != EOF) {
        memset(dp[0], 0x3f, sizeof(dp[0]));
        dp[0][0] = 0;
        tmp_block.clear();
        block.clear();
        for (int i = 1; i <= n; i++) {
            long long w = 0,h = 0;
            scanf(" %lld %lld",&w,&h);
            tmp_block.push_back(make_pair(h, w));
        }
        sort(tmp_block.begin(), tmp_block.end(), cmp);
        long long curmin = maxll;
        for (int i = 1; i <= n ; i++) {
            if (tmp_block[i-1].second <= curmin) {
                block.push_back(tmp_block[i-1]);
            }
            curmin = tmp_block[i-1].second;
        }
        n = block.size();
        block.push_back(make_pair(0, 0));
        long long res = maxll;
        for (int t = 1; t <= k; t++) {
            head = tail = 0;
            que[tail++] = t-1;
            for (int i = t; i <= n; i++) {
                while (head + 1 < tail
                       && slope_upper(t, que[head + 1], que[head]) <= block[i-1].first * slope_lower(que[head + 1], que[head])) {
                    head++;
                }
                dp[t%2][i] = get_dp(t, i, head);
                while (head + 1 < tail
                       && slope_upper(t, que[tail - 2], que[tail - 1]) * slope_lower(que[tail - 1], i) >= slope_lower(que[tail - 2], que[tail - 1]) * slope_upper(t, que[tail - 1], i)) {
                    tail--;
                }
                que[tail++] = i;
            }
            res = min(res, dp[t%2][n]);
        }
        cout << res << endl;
    }
    
    return 0;
}
