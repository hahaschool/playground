//
//  TCSuccessiveSubtraction2.cpp
//  playground
//
//  Created by 張正昊 on 19/5/2016.
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

void upd(int &oldval,int attval){
    oldval = max(oldval,attval);
}

class SuccessiveSubtraction2{
public:
    vector<int> A;
    int n;
    static const int MAXN = 2005;
    int dp[MAXN][3][3];
    int solve(){
        memset(dp, 0xf3, sizeof(dp));
        memset(dp[1], 0, sizeof(dp[1]));
        for (int i = 1; i < n; i++) {
            for (int j = 0,sgn = -1; j <= 2; j++,sgn*=-1) {
                if(i == 1 && j) continue;
                for (int k = 0; k <= 2; k++) {
                    if(k){
                        //try creating new bracket
                        upd(dp[i+1][j+1][k-1],dp[i][j][k]+sgn*A[i]);
                    }
                    if(j){
                        //try enclosing existing bracket
                        upd(dp[i+1][j-1][k],dp[i][j][k]+sgn*A[i]);
                    }
                    //do nothing with bracket
                    upd(dp[i+1][j][k],dp[i][j][k]+sgn*A[i]);
                }
            }
        }
        return dp[n][0][0] + A[0];
    }
    
    vector<int> calc(vector<int> a,vector<int> p,vector<int> v){
        vector<int> ret;
        A = a;
        n = A.size();
        for (int i = 0; i < p.size(); i++) {
            A[p[i]] = v[i];
            ret.push_back(solve());
        }
        return ret;
    }
};

SuccessiveSubtraction2 solver;

void commitTest(vector<int> a,vector<int> b,vector<int> c){
    vector<int> ret = solver.calc(a, b, c);
    cout << '{';
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i];
        if (i == ret.size()-1) {
            cout << "}" << endl;
        }else{
            cout << ',';
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest({1, 2, 3, 4, 5},{1, 2, 0, 4, 3},{3, 9, -10, 5, 1});
    commitTest({-100, -100, -100, -100, -100},{0, 1, 2, 3, 4},{0, 0, 0, 0, 0});
    commitTest({83, 0, 25, 21},{0, 3, 2, 1, 3, 1, 2},{10, -90, 33, 52, -100, 0, 45});
    commitTest({1},{0, 0, 0, 0},{10, -10, 100, -100});
    commitTest({-11, -4, 28, 38, 21, -29, -45, 11, -58, -39, 92, 35, -56, -6, 29, -2, 61, 10, -29, -63},{19, 5, 3, 10, 4, 18, 5, 2, 0, 15},{-19, 21, 7, -66, 38, -39, -22, 24, -32, 13});

    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
