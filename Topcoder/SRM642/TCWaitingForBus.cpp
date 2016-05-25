//
//  TCWaitingForBus.cpp
//  playground
//
//  Created by 張正昊 on 24/5/2016.
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

class WaitingForBus{
public:
    static const int MAXN = 200005;
    double dp[MAXN];
    double whenWillBusArrive(vector<int> time,vector<int> prob,int s){
        memset(dp, 0, sizeof(dp));
        int mxt = 0;
        for (int i = 0; i < time.size(); i++) {
            mxt = max(mxt,time[i]);
        }
        
        dp[0] = 1;
        for (int i = 1; i <= s; i++) {
            for (int j = 0; j < time.size(); j++) {
                if(i-time[j] >= 0) {
                    dp[i] += dp[i-time[j]] * ((double)prob[j]/(double)100);
                }
            }
        }
        for (int i = s+1; i <= s+mxt; i++) {
            for (int j = 0; j < time.size(); j++) {
                if(i-time[j] >= 0 && i-time[j] < s){
                    dp[i] += dp[i-time[j]] * ((double)prob[j]/(double)100);
                }
            }
        }
        double ret = 0;
        for (int i = s; i <= s+mxt; i++) {
            ret += dp[i]*(double)(i-s);
        }
        return ret;
    }
    WaitingForBus(){}
};

WaitingForBus solver;
void commitTest(vector<int> a,vector<int> b,int c){
    cout << fixed << setprecision(10) <<solver.whenWillBusArrive(a, b, c) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest({5,100}, {90,10}, 5);
    commitTest({5},{100},101);
    commitTest({5,10},{50,50},88888);
    commitTest({1,2,3,4},{10,20,30,40},1000);
    commitTest({10,100,1000,10000,100000},{90,4,3,2,1},100000);
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
