//
//  UVA10341.cpp
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

double p,q,r,s,t,u;
double f(double x){
    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    while (scanf(" %lf %lf %lf %lf %lf %lf",&p,&q,&r,&s,&t,&u) != EOF) {
        double lt = f(0),rt = f(1);
        if (lt*rt > 0) {
            puts("No solution");
            continue;
        }
        double l = 0,r = 1,mid;
        for(int i = 1; i <= 25; i++){
            mid = (l+r)/2.0;
            if(f(mid) > 0){
                l = mid;
            }else{
                r = mid;
            }
        }
        printf("%.4lf\n",l);
    }
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
