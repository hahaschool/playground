//
//  TCTheProgrammingContestDivOne.cpp
//  playground
//
//  Created by 張正昊 on 18/7/2016.
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

class TheProgrammingContestDivOne{
public:
    static const int MAXT = 200005;
    long long T,N;
    struct Item{
        long long m,p,r;
        bool operator < (const Item &b) const{
            if(r*b.p == b.r*p) return m > b.m;
            return r*b.p < b.r*p;
        }
    };
    vector<Item> item;
    long long dp[2][MAXT];
    int solve(){
        sort(item.begin(), item.end());
        memset(dp, 0, sizeof(dp));
        long long Res = 0;
        for (int i = 0; i < N; i++) {
            memset(dp[(i+1)%2], 0, sizeof(dp[(i+1)%2]));
            for (int j = 0; j <= T; j++) {
                long long res = 0;
                if(j-item[i].r >= 0){
                    res = item[i].m - item[i].p * ((long long)j);
                    res += dp[i%2][j-item[i].r];
                }
                res = max(res,dp[i%2][j]);
                res = max(res,dp[(i+1)%2][j]);
                
                dp[(i+1)%2][j] = res;
                Res = max(Res,res);
            }
        }
        return Res;
    }
    
    int find(int _T,vector<int> _maxPoints,vector<int> _pointsPerMinute,vector<int> _requiredTime){
        T = _T,N = _maxPoints.size();
        item.clear();
        for (int i = 0; i < N; i++) {
            item.push_back((Item){_maxPoints[i],_pointsPerMinute[i],_requiredTime[i]});
        }
        return solve();
    }
    TheProgrammingContestDivOne(){}
};

TheProgrammingContestDivOne solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.find(100000, {43870, 35630, 64332, 29314, 91810, 30713, 92083, 34545, 43527, 8873, 21291, 94124, 29550, 3194, 13615, 95718, 99109, 37404, 55083, 46488, 54658, 52121, 24121, 75630, 92015, 31444, 26858, 83371, 16195, 32506, 28091, 82145, 8476, 19109, 65026, 11354, 90026, 27670, 60557, 59395, 51931, 80999, 15095, 49606, 86010, 50608, 89208, 64485, 15134, 6368}, {3, 1, 8, 2, 2, 6, 7, 8, 1, 3, 8, 4, 1, 6, 10, 5, 7, 8, 6, 3, 10, 10, 2, 5, 4, 9, 4, 4, 5, 7, 8, 6, 8, 5, 10, 9, 2, 9, 4, 3, 10, 7, 3, 4, 9, 6, 10, 6, 2, 3}, {6309, 173, 7391, 6248, 4064, 7879, 1158, 290, 2884, 7320, 6407, 3283, 2389, 433, 290, 8899, 2240, 8127, 8931, 4111, 1159, 2279, 2104, 3755, 4672, 2414, 3974, 8038, 1926, 7489, 469, 4875, 2741, 7641, 6296, 1737, 2513, 6449, 6312, 2901, 6967, 4875, 4594, 9131, 4658, 8092, 3541, 2247, 6900, 5777}

) << endl;
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
