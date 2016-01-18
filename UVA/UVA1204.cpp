//
//  UVA1204.cpp
//  playground
//
//  Created by 張正昊 on 18/1/2016.
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
char str[20][105];
char inv[20][105];
int len[20];
int crs[20][20][2][2];

int calcCrs(char *a,char *b){
    int lena = (int)strlen(a),lenb = (int)strlen(b);
    for(int i = 1; i < lena; i++){
        if(i + lenb <= lena){
            continue;
        }
        bool flag = true;
        for(int j = 0; j+i < lena; j++){
            if(a[j+i] != b[j]){
                flag = false;
                break;
            }
        }
        if(flag){
            return lena - i;
        }
    }
    return 0;
}

void preProc(){
    //eliminate inner cross strings
    for(int i = 1; i<= n; i++){
        len[i] = (int)strlen(str[i]);
        memcpy(inv[i], str[i], sizeof(str[i]));
        reverse(inv[i], inv[i]+len[i]);
    }
    bool del[20] = {};
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= n; j++){
            if(i == j || del[j]){
                continue;
            }
            char *mkr = strstr(str[j], str[i]);
            char *invmkr = strstr(inv[j], str[i]);
            if (mkr == NULL && invmkr == NULL) {
                continue;
            }else{
                del[i] = true;
                break;
            }
        }
    }
    int nn = 0;
    for (int i = 1; i <= n; i++) {
        if (!del[i]) {
            swap(str[i], str[++nn]);
            swap(inv[i], inv[nn]);
            swap(del[i], del[nn]);
        }
    }
    n = nn;
    
    //preproccess crossing
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            crs[i][j][0][0] = calcCrs(str[i], str[j]);
            crs[i][j][1][1] = calcCrs(inv[i], inv[j]);
            crs[i][j][0][1] = calcCrs(str[i], inv[j]);
            crs[i][j][1][0] = calcCrs(inv[i], str[j]);
        }
    }
}

int msk_full = 0;
int dp[70000][20][2]; //minimum len,when in selection msk i,last one being j,direction indicated by k

int solve(){
    preProc();
    msk_full = (1 << n) - 1;
    for(int i = 0; i <= msk_full; i++){
        for(int j = 1; j <= n; j++){
            dp[i][j][0] = dp[i][j][1] = 0x3f3f3f3f;
        }
    }
    dp[1][1][0] = len[1];//force No.1 string be orthodirectional!
    
    for(int i = 0; i < msk_full; i++){
        for(int j = 1; j <= n; j++){
            if(i & (1 << (j-1))){
                for(int k = 1; k <= n; k++){
                    int msk = 1 << (k-1);
                    if((msk & i) == 0){
                        dp[msk|i][k][0] = min(dp[msk|i][k][0],dp[i][j][0] + len[k] - crs[j][k][0][0]);
                        dp[msk|i][k][0] = min(dp[msk|i][k][0],dp[i][j][1] + len[k] - crs[j][k][1][0]);
                        dp[msk|i][k][1] = min(dp[msk|i][k][1],dp[i][j][0] + len[k] - crs[j][k][0][1]);
                        dp[msk|i][k][1] = min(dp[msk|i][k][1],dp[i][j][1] + len[k] - crs[j][k][1][1]);
                    }
                }
            }
        }
    }
    
    int ret = 0x3f3f3f3f;
    for(int i = 1; i<= n; i++){
        ret = min(ret,dp[msk_full][i][0] - crs[i][1][0][0]);
        ret = min(ret,dp[msk_full][i][1] - crs[i][1][1][0]);
    }
    if(ret < 2) ret = 2;
    return ret;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
#endif
    while(scanf(" %d",&n) != EOF){
        if(!n){
            break;
        }
        for(int i = 1; i<= n; i++){
            scanf(" %s",str[i]);
        }
        preProc();
        printf("%d\n",solve());
    }
    
    
    return 0;
}
