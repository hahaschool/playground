//
//  HDU4089.cpp
//  playground
//
//  Created by Adam Chang on 2015/4/5.
//  Copyright (c) 2015年 Adam Chang. All rights reserved.
//

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

int n,m,k;
double p1,p2,p3,p4;
double pd[2001];
double dp[2][2000];
const double eps=1e-5;

inline double con(int i,int j){
    if(j < k)
        return dp[(i-1)%2][j-1]*p3+p4;
    else return dp[(i-1)%2][j-1]*p3;
}

int main(){
    while (cin >> n >> m >> k >> p1 >> p2 >> p3 >> p4) {
        //WARNING THIS IS VERY KENG
        if(p4<eps)
        {
            printf("0.00000\n");
            continue;
        }//if the prob of system dwn is lower than eps,then the system won't down
        //this statement must be made or you will receive a WA-_-#
        
        //init
        memset(dp, 0, sizeof(dp));
        memset(pd, 0, sizeof(pd));
        dp[1][0] = p4/(1-p1-p2);
        pd[0] = 1,pd[1] = p2/(1-p1);
        for (int i = 2; i <= n; i++) {
            pd[i] = pd[i-1]*pd[1];
        }
        for (int i = 2; i <= n; i++) {
            //get dp[i][i-1] and dp[i][0]
            double sigma = 0;
            for (int j = 0; j <= i-2; j++) {
                sigma += pd[j]*con(i,i-1-j)/(1-p1);
            }
            dp[i%2][i-1] = (pd[i-1]*p4/(1-p1)+sigma)/(1-pd[i]);
            dp[i%2][0] = (p2*dp[i%2][i-1]+p4)/(1-p1);
            //dp start
            for (int j = 1; j <= i-1; j++) {
                dp[i%2][j] = (p2*dp[i%2][j-1]+con(i,j))/(1-p1);
            }
        }
        printf("%.5lf\n",dp[n%2][m-1]);
        
    }
    return 0;
}
