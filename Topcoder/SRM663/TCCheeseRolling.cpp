//
//  TCCheeseRolling.cpp
//  playground
//
//  Created by 張正昊 on 13/5/2016.
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

class CheeseRolling{
public:
    static const int MAXN = 5;
    bool win[MAXN][MAXN];
    int n;
    long long dp[MAXN][1 << MAXN];
    void solve(int cur){
        int haf = cur >> 1;
        for (int S = 0; S < (1 << n); S++) {
            if (__builtin_popcount(S) == cur) {
                for (int L = S; L; L = (L-1)&S) {
                    if(__builtin_popcount(L) == haf){
                        int R = S^L;
                        for (int i = 0; i < n; i++) {
                            if (L & (1 << i)) {
                                for (int j = 0; j < n; j++) {
                                    if (R & (1 << j)) {
                                        if(win[i][j]) dp[i][S] += dp[i][L]*dp[j][R];
                                        if(win[j][i]) dp[j][S] += dp[i][L]*dp[j][R];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vector<long long> waysToWin(vector<string> wins){
        n = wins.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                win[i][j] = wins[i][j] == 'Y';
            }
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            dp[i][1<<i] = 1;
        }
        for (int i = 2; i <= n; i <<= 1) {
            solve(i);
        }
        vector<long long> ret;ret.resize(n);
        for (int i = 0; i < n; i++) {
            ret[i] = dp[i][(1 << n)-1];
        }
        return ret;
    }
};


CheeseRolling solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    int n;
    cin >> n;
    vector<string> a;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        a.push_back(str);
    }
    vector<long long> re = solver.waysToWin(a);
    for (int i = 0; i < re.size(); i++) {
        cout << re[i] << endl;
    }
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
