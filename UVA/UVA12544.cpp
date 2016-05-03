//
//  UVA12544.cpp
//  playground
//
//  Created by 張正昊 on 30/4/2016.
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
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <cmath>
#include <map>
#include <complex>
#include <list>

using namespace std;

int seq[7];
int t;
int apr;

int park[22];
bool vis[22];
int pl,pr;

int bsa[22],bsb[22],bsop[22],bsr;
int tma[22],tmb[22],tmop[22],tmr;

void commit(){
    for (int i = 1; i <= tmr; i++) {
        bsa[i] = tma[i];
        bsb[i] = tmb[i];
        bsop[i] = tmop[i];
    }
    bsr = tmr;
}

void dfs(int cur){
    if (apr == 0 || park[pr] <= 0) return;
    if (abs(park[pr]-t) < apr) {
        apr = abs(park[pr]-t);
        commit();
    }
    if(cur == 6) return;
    for(int i = 1;i <= pr; i++){
        for (int j = 1; j <= pr; j++) {
            if(i != j && !vis[i] && !vis[j]){
                int a = park[i],b = park[j];
                tma[cur] = a,tmb[cur] = b;
                vis[i] = vis[j] = true;
                pr++;
                tmr++;
                if (i < j) {
                    park[pr] = a+b;
                    tmop[cur] = 1;
                    dfs(cur+1);
                    park[pr] = a*b;
                    tmop[cur] = 3;
                    dfs(cur+1);
                }
                if (a > b) {
                    park[pr] = a-b;
                    tmop[cur] = 2;
                    dfs(cur+1);
                }
                if (a >= b && b && a%b == 0) {
                    park[pr] = a/b;
                    tmop[cur] = 4;
                    dfs(cur+1);
                }
                tmr--;
                pr--;
                vis[i] = vis[j] = false;
            }
        }
    }
}

void solve(){
    apr = 0x3f3f3f3f;
    for (int i = 1; i <= 6; i++) {
        park[i] = seq[i];
    }
    pl = 1,pr = 6;
    dfs(1);
    int bsres = 0;
    printf("Target: %d\n",t);
    for (int i = 1; i <= bsr; i++) {
        bsres = bsa[i];
        printf("%d ",bsa[i]);
        if (bsop[i] == 1) {
            putchar('+');
            bsres += bsb[i];
        }
        if (bsop[i] == 2) {
            putchar('-');
            bsres -= bsb[i];
        }
        if (bsop[i] == 3) {
            putchar('*');
            bsres *= bsb[i];
        }
        if (bsop[i] == 4) {
            putchar('/');
            bsres /= bsb[i];
        }
        printf(" %d = %d\n",bsb[i],bsres);
    }
    printf("Best approx: %d\n",bsres);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        if(d>1) puts("");
        for(int i = 1; i <= 6; i++){
            scanf(" %d",&seq[i]);
        }
        scanf(" %d",&t);
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}

