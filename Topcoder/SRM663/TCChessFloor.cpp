//
//  TCChessFloor.cpp
//  playground
//
//  Created by 張正昊 on 14/5/2016.
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

class ChessFloor{
public:
    static const int MAXN = 22;
    int n;
    char board[MAXN][MAXN];
    int check(char a,char b){
        int tick = 1,ret = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if(tick) ret += (board[i][j] == a)?0:1;
                else ret += (board[i][j] == b)?0:1;
                tick ^= 1;
            }
            if(!(n&1)) tick ^= 1;
        }
        return ret;
    }
    
    
    int minimumChanges(vector <string> floor){
        n = floor.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i+1][j+1] = floor[i][j];
            }
        }
        int res = 0x3f3f3f3f;
        for (char i = 'a'; i <= 'z'; i++) {
            for (char j = 'a'; j <= 'z'; j++) {
                if(i != j) res = min(res,check(i, j));
            }
        }
        return res;
    }
};

ChessFloor solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    solver.n = 3;
    solver.check('s', 'd');
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
