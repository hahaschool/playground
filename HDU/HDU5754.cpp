//
//  HDUMUTC3.cpp
//  playground
//
//  Created by 張正昊 on 26/7/2016.
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

const int MAXN = 1005;
int dp[MAXN][MAXN]; //-1:N/A 1:winwin 2:loselose 3:drawdraw
int typ;
int n,m;
//1:king DRA1
//2:rock DRx
//3:knight D1+A1 R1+A1
//4:queen LRAx

bool inbound(int r,int c){
    return (r >= 1 && r <= n) && (c >= 1 && c <= m);
}


int dsum_hor[MAXN][MAXN],dsum_vec[MAXN][MAXN],dsum_dia[MAXN*2][MAXN];

int dfs(int r,int c){
    if(dp[r][c] != -1) return dp[r][c];
    if(!inbound(r, c)) return 0;
    if(r == n && c == m) {
        dp[r][c] = 1<<2;
        dsum_hor[r][c] = dp[r][c] | dsum_hor[r][c+1];
        dsum_vec[c][r] = dp[r][c] | dsum_vec[c][r+1];
        dsum_dia[r][c] = dp[r][c] | dsum_dia[r+1][c+1];
        return dp[r][c];
    }
    
    int flg = 0;//win lose draw
    if(typ == 1){
        flg |= dfs(r+1, c);
        flg |= dfs(r, c+1);
        flg |= dfs(r+1, c+1);
    }else if(typ == 2){
        dfs(r+1, c);
        flg |= dsum_vec[c][r+1];
        
        dfs(r, c+1);
        flg |= dsum_hor[r][c+1];
    }else if(typ == 3){
        flg |= dfs(r+2, c+1);
        flg |= dfs(r+1, c+2);
    }else if(typ == 4){
        dfs(r+1, c);
        flg |= dsum_vec[c][r+1];
        
        dfs(r, c+1);
        flg |= dsum_hor[r][c+1];
        
        dfs(r+1,c+1);
        flg |= dsum_dia[r+1][c+1];
    }
    
    
    
    if(((flg&(1<<1)) == 0) && (((flg&(1<<2))) == 0) && ((flg&(1<<3)) == 0)){
        dp[r][c] = 1<<3;
    }else if(((flg&(1<<2)))){
        dp[r][c] = 1<<1;
    }else if(((flg&(1<<3)))){
        dp[r][c] = 1<<3;
    }else dp[r][c] = 1<<2;
    
    dsum_hor[r][c] = dp[r][c] | dsum_hor[r][c+1];
    dsum_vec[c][r] = dp[r][c] | dsum_vec[c][r+1];
    dsum_dia[r][c] = dp[r][c] | dsum_dia[r+1][c+1];
    return dp[r][c];
}


int main(int argc, const char * argv[]){
#ifdef LOCAL_DEBUG
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    
    typ = 4;
    for (n = 1; n <= 1000; n++) {
        for (m = 1; m <= 1000; m++) {
            memset(dp, -1, sizeof(dp));
            memset(dsum_vec,0, sizeof(dsum_vec));
            memset(dsum_dia, 0, sizeof(dsum_dia));
            memset(dsum_hor, 0, sizeof(dsum_hor));
            int res = dfs(1, 1);
            if(res != 1<<1){
                cout << m << endl;
                break;
            }
        }
        putchar(',');
    }
    
    
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d %d %d",&typ,&n,&m);
        if(typ == 1){
            if(n&1){
                if(m&1) puts("G");
                else puts("B");
            }else puts("B");
        }else if(typ == 2){
            if(n == m) puts("G");
            else puts("B");
        }else if(typ == 3){
            if(n%3 == 1){
                if(n == m) puts("G");
                else puts("D");
            }else{
                if(abs(n-m)==1) puts("B");
                else puts("D");
            }
        }else {
            memset(dp, -1, sizeof(dp));
            memset(dsum_vec,0, sizeof(dsum_vec));
            memset(dsum_dia, 0, sizeof(dsum_dia));
            memset(dsum_hor, 0, sizeof(dsum_hor));
            int res = dfs(1, 1);
            if(res == 1<<3) puts("D");
            else if(res == 1<<2) puts("G");
            else puts("B");
        }
        
    }
    
    
    
    
    
#ifdef LOCAL_DEBUG
    puts("-----END OF OUTPUT-----");
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
