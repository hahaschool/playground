//
//  UVA11427.cpp
//  playground
//
//  Created by 張正昊 on 25/4/2016.
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
int upper,lower,n;

const double EPS = 1e-8;
int dcmp(double a,double b){
    if (abs(a-b) < EPS) {
        return 0;
    }
    else return a-b>0?1:-1;
}

double p[MAXN][MAXN];
void solve(){
    double wp = (double)upper/(double)lower;
    memset(p, 0, sizeof(p));
    p[1][0] = 1.0-wp, p[1][1] = wp;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double cp = (double)j/(double)i;
            if (dcmp(cp, wp) <= 0) {
                p[i+1][j] += p[i][j] * (1.0-wp);
                p[i+1][j+1] += p[i][j] * wp;
            }else break;
        }
    }
    
    double q = 0;
    for (int i = 0; i <= n; i++) {
        double cp = (double)i/(double)n;
        if (dcmp(cp, wp) <= 0) {
            q += p[n][i];
        }else break;
    }
    printf("%d\n",(int)(1/q));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt; d++){
        printf("Case #%d: ",d);
        scanf(" %d/%d %d",&upper,&lower,&n);
        solve();
    }
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
