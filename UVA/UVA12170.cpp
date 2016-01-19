//
//  UVA12170.cpp
//  playground
//
//  Created by 張正昊 on 19/1/2016.
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
long long d;
int n;
long long h[MAXN];
vector<long long> disc;
int tot;
long long dp[MAXN][MAXN*MAXN*2];//dp[current no.][last id.] = min cost
//ISSUE2: 在这里的两个MAXN*MAXN在考虑了-n范围之后，没有乘2，数组开小了导致结果异常
int que[MAXN*MAXN*2],head,tail;
bool que_empty(){
    return head >= tail;
}
void que_pop(){
    if(!que_empty()){
        head++;
    }
}
void que_push(int i,int id){
    while (!que_empty() && dp[i][que[tail-1]] >= dp[i][id]) {
        tail--;
    }
    que[tail] = id;
    tail++;
}
void solve(){
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < tot; j++){
            dp[i][j] = 0x3f3f3f3f3f3f3f3f;
        }
    }
    for(int i = 0; i < tot; i++){
        if(disc[i] == h[1]){
            dp[1][i] = 0;
            break;
        }
    }
    
    for(int i = 2; i <= n-1; i++){
        int cur = 0;
        head = tail = 0;
        for(int j = 0; j < tot; j++){
            while (!que_empty() && (disc[que[head]] < disc[j]-d || disc[que[head]] > disc[j]+d)) {
                que_pop();
            }
            while(cur < tot && disc[cur] >= disc[j]-d && disc[cur] <= disc[j]+d){
                que_push(i-1,cur);
                cur++;
            }
            dp[i][j] = abs(h[i] - disc[j]) + dp[i-1][que[head]];
        }
    }
    long long ans = 0x3f3f3f3f3f3f3f3f;
    for(int i = 0; i < tot; i++){
        if(disc[i] >= h[n] - d && disc[i] <= h[n] + d)
        ans = min(ans,dp[n-1][i]);
    }
    if(ans > 0x3f3f3f3f3f3f3f){
        puts("impossible");
        return;
    }
    printf("%lld\n",ans);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int cas = 1;cas <= caseCnt ;cas++){
        scanf(" %d %lld",&n,&d);
        for(int i = 1; i <= n; i++){
            scanf(" %lld",&h[i]);
        }
        disc.clear();
        for(int i = 1; i<= n; i++){
            for(long long j = -n; j <= n; j++){//ISSUE1: 这里原来写的是j=0 这样就漏状态了（相当于只能＋d不能－d了）
                    disc.push_back(h[i] + j * d);
            }
        }
        sort(disc.begin(), disc.end());
        disc.erase(unique(disc.begin(), disc.end()),disc.end());
        tot = (int)disc.size();
        solve();
    }
    
    return 0;
}

//ISSUE3:无解的检查方法最开始是不对的，题目只要求了相邻的两个数差距小于等于d，不应该使用全局的lower bound和upper bound。正确的方法是利用最后的h[n]再判一次
//ATT:注意单调队列的实现，更重要的是如何分析问题把大状态范围缩小到可以dp的程度（发现规律（有一点贪心的想法），剔除无用状态）。
