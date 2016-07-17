//
//  TCCutSticks.cpp
//  playground
//
//  Created by 張正昊 on 17/7/2016.
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

//题意是一根棍子分割点随意，不是对半
//二分的时候，可以用double预判数字大小来防爆

class CutSticks{
public:
    vector<int> sticks;
    int C,K;
    
    
    bool check(double target){
        long long rnk = 0;
        long long rem = C;
        for (int i = 0; i < sticks.size(); i++) {
            if(rnk >= K) break;
            long long produce;
            if((double)sticks[i] / target > (double)K) produce = K;
            else produce = (long long)floor((double)sticks[i] / target);
            if(produce) rnk++;
            if(produce >= 2){
                rnk += min(produce-1,rem);
                rem -= min(produce-1,rem);
            }
        }
        return rnk >= K;
    }
    
    double solve(){
        double l = 0,r = *max_element(sticks.begin(), sticks.end()),mid;
        for (int i = 1; i <= 100; i++) {
            mid = (l+r)/2;
            if(check(mid)) l = mid;
            else r = mid;
        }
        return mid;
    }
    
    double maxKth(vector<int> _sticks,int _C,int _K){
        sticks = _sticks;
        C = _C;
        K = _K;
        return solve();
    }
    
    CutSticks(){}
};

CutSticks solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.maxKth({5,8}, 1, 1) << endl;
    cout << solver.maxKth({5,8}, 1, 2) << endl;
    cout << solver.maxKth({5,8}, 1, 3) << endl;
    cout << solver.maxKth({1000000000, 1000000000, 1},2,5) << endl;
    cout << solver.maxKth({76, 594, 17, 6984, 26, 57, 9, 876, 5816, 73, 969, 527, 49},789,456) << endl;
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
