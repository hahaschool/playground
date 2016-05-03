//
//  LA5009.cpp
//  playground
//
//  Created by 張正昊 on 29/4/2016.
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

const int MAXN = 10005;
double a[MAXN],b[MAXN],c[MAXN];
int n;

double f(double x){
    double ret = a[1]*x*x+b[1]*x+c[1];
    for(int i = 1; i <= n; i++){
        ret = max(ret,a[i]*x*x+b[i]*x+c[i]);
    }
    return ret;
}

void solve(){
    double l = 0,r = 1000;
    for (int i = 1; i <= 100; i++) {
        double ll = l+(r-l)/3;
        double rr = r-(r-l)/3;
        if(f(ll) < f(rr)){
            r = rr;
        }else{
            l = ll;
        }
    }
    printf("%.4lf\n",f(l));
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for (int d = 1; d <= caseCnt; d++) {
        scanf(" %d",&n);
        for(int i = 1; i <= n;i++){
            scanf(" %lf %lf %lf",&a[i],&b[i],&c[i]);
        }
        solve();
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
