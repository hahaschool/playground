//
//  POJ2096.cpp
//  playground
//
//  Created by Adam Chang on 2015/3/27.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//
/*
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

using namespace std;

double dp[1010][1010];

int main(){
    int in = 0,im = 0;
    while (cin >> in >> im) {
        double n = in,m = im;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 0;
        for (int ii = 1; ii <= in; ii++) {
            double i = ii;
            dp[ii][0] = dp[ii-1][0] + n/i;
        }
        for (int ii = 1; ii <= im; ii++) {
            double i = ii;
            dp[0][ii] = dp[0][ii-1] + m/i;
        }
        for (int ii = 1; ii <= in; ii++) {
            for (int ij = 1; ij <= im; ij++) {
                double i = ii,j = ij;
                dp[ii][ij] = (i*j)*dp[ii-1][ij-1]+(n-i)*j*dp[ii][ij-1]+i*(m-j)*dp[ii-1][ij]+m*n;
                dp[ii][ij] /= m*n-(n-i)*(m-j);
            }
        }
        printf("%.4lf\n",dp[in][im]);
    }
    return 0;
}*/
