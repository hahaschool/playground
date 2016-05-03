//
//  LA3485.cpp
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

double D,H,B,L;
double PAR;//PAR = 4h/w^2
double f(double x){
    return sqrt(1+4*PAR*PAR*x*x);
}

double simpson(double a,double b){
    double c = a + (b-a)/2;
    return (f(a) + 4*f(c) + f(b))*(b-a)/6;
}

double asr(double a,double b,double eps,double A){
    double c = a + (b-a)/2;
    double l = simpson(a, c),r = simpson(c, b);
    if(abs(l+r-A) <= 15*eps) return l+r+(l+r-A)/15.0;
    return asr(a,c,eps/2,l) + asr(c, b, eps/2, r);
}

double asr(double a,double b,double eps){
    return asr(a,b,eps,simpson(a, b));
}

const double EPS = 1e-11;
int dcmp(double a,double b){
    if(fabs(a-b) < EPS) return 0;
    return (a>b)?1:-1;
}

void solve(){
    double n = ceil(B/D);
    double w = B/n;
    double ll = L/n;
    double l = 0,r = H,mid;
    for(int i = 1; i <= 104; i++){
        mid = l + (r - l)/2;
        PAR = 4*mid/w/w;
        if (asr(0, w/2, EPS) * 2.0 > ll) {
            r = mid;
        }else{
            l = mid;
        }
    }
    printf("%.2lf\n",H-l);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int caseCnt;
    scanf(" %d",&caseCnt);
    for(int d = 0;d < caseCnt;d++){
        if(d) puts("");
        printf("Case %d:\n",d+1);
        scanf(" %lf %lf %lf %lf",&D,&H,&B,&L);
        solve();
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
