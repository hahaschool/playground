//
//  LA3983.cpp
//  playground
//
//  Created by 張正昊 on 21/2/2016.
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

const long long MAXN = 100005;
long long c,n;
struct Point{
    long long x,y,w;
} point[MAXN];
long long que[MAXN];
long long head,tail;
void clear(){
    head = tail = 0;
    que[0] = 0;
}

long long mhtsum[MAXN];
long long wsum[MAXN];
long long dp[MAXN];

inline long long mht(long long a,long long b){
    long long xm = abs(point[a].x - point[b].x);
    long long ym = abs(point[a].y - point[b].y);
    return xm + ym;
}

void getMhtSum(){
    mhtsum[1] = 0;
    for(long long i = 2; i <= n; i++){
        mhtsum[i] = mhtsum[i-1] + mht(i-1, i);
    }
}

void getWSum(){
    wsum[0] = 0;
    for(long long i = 1; i<= n; i++){
        wsum[i] = wsum[i-1] + point[i].w;
    }
}

inline long long totw(long long a,long long b){
    return wsum[b] - wsum[a-1];
}

inline long long totmht(long long a,long long b){
    return mhtsum[b] - mhtsum[a];
}

inline long long f(long long j){
    return dp[j-1] + mht(0,j) - totmht(1,j);
}

void push(long long a){
    while (tail > head) {
        if (f(que[tail - 1]) > f(a)) {
            tail--;
        }else{
            break;
        }
    }
    que[tail++] = a;
}

long long pop(long long i){
    while (tail > head) {
        if (totw(que[head],i) > c) {
            head++;
        }else{
            break;
        }
    }
    if (tail == head) {
        return i;
    }
    return que[head];
}

void solve(){
    clear();
    getMhtSum();
    getWSum();
    dp[0] = 0;
    for(long long i = 1; i <= n; i++){
        push(i);
        dp[i] = f(pop(i)) + totmht(1, i) + mht(0,i);
    }
    printf("%lld\n",dp[n]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        if (d > 1) {
            puts("");
        }
        scanf(" %lld %lld",&c,&n);
        for(int i = 1; i<= n; i++){
            scanf(" %lld %lld %lld",&point[i].x,&point[i].y,&point[i].w);
        }
        solve();
    }
    return 0;
}