//
//  UVA12099.cpp
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

const int MAXN = 75;
const int MAXW = 2105;
int n;
struct Book{
    int h,w;
    bool operator < (const Book &b) const{
        return h > b.h || (h == b.h && w > b.w);
    }
} book[MAXN];
int dp[2][MAXW][MAXW];
int sumw[MAXN];

int sgn(int a, int b){
    if(a == 0){
        return b;
    }
    return 0;
}

void upd(int &tar,int to){
    tar = min(tar,to);
}

void solve(){
    //init
    sort(book+1, book+1+n);
    for(int i = 1;i <= n; i++){
        sumw[i] = sumw[i-1] + book[i].w;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0][0] = 0;
    int tick = 0;
    for(int i = 1; i < n; i++){
        for(int j = 0; j <= sumw[i+1] ; j++){
            for (int k = 0; j+k <= sumw[i+1]; k++) {
                dp[tick^1][j][k] = 0x3f3f3f3f;
            }
        }
        dp[1][0][0] = dp[0][0][0] = 0;
        for(int j = 0; j <= sumw[i+1]; j++){
            for(int k = 0; j+k<= sumw[i+1]; k++){
                if(dp[tick][j][k] == 0x3f3f3f3f){
                    continue;
                }
                upd(dp[tick^1][j][k], dp[tick][j][k]);
                upd(dp[tick^1][j+book[i+1].w][k], dp[tick][j][k] + sgn(j, book[i+1].h));
                upd(dp[tick^1][j][k+book[i+1].w], dp[tick][j][k] + sgn(k, book[i+1].h));
            }
        }
        tick ^= 1;
    }
    int ret = 0x3f3f3f3f;
    for(int i = 1; i <= sumw[n]; i++){
        for(int j = 1; i+j <= sumw[n]; j++){
            if(dp[tick][i][j] != 0x3f3f3f3f){
                ret = min(ret,max(sumw[n]-i-j,max(i,j)) * (dp[tick][i][j]+book[1].h));
            }
        }
    }
    printf("%d\n",ret);
}

int main(){
    int caseCnt = 0;
    scanf(" %d",&caseCnt);
    for(int d = 1; d <= caseCnt;d++){
        scanf(" %d",&n);
        for(int i = 1; i <= n; i++){
            scanf(" %d %d",&book[i].h,&book[i].w);
        }
        solve();
    }
    return 0;
}
