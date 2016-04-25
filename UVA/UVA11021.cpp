//
//  UVA11021.cpp
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

const int MAXN = 1005;
int n,k,m;
double bp[MAXN];

double p[MAXN];

void solve(){
    memset(p, 0, sizeof(p));
    for (int i = 1; i <= m; i++) {
        double fac = 1;
        double ret = 0;
        for (int j = 0; j < n; j++) {
            ret += fac*bp[j];
            fac *= p[i-1];
        }
        p[i] = ret;
    }
    double res = 1;
    for(int i = 1; i <= k; i++){
        res *= p[m];
    }
    printf("%.7lf\n",res);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 1;d <= caseCnt;d++){
        printf("Case #%d: ",d);
        scanf(" %d %d %d",&n,&k,&m);
        for (int i = 0; i < n; i++) {
            scanf(" %lf",&bp[i]);
        }
        solve();
    }
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
