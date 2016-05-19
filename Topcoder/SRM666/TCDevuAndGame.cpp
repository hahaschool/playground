//
//  TCDevuAndGame.cpp
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

class DevuAndGame{
public:
    vector<int> to;
    int n;
    bool vis[55];
    bool dfs(int u){
        vis[u] = true;
        if (to[u] == -1) {
            return true;
        }
        if (vis[to[u]]) {
            return false;
        }
        return dfs(to[u]);
    }
    
    string canWin(vector<int> nextLevel){
        memset(vis, 0, sizeof(vis));
        n = nextLevel.size();
        to = nextLevel;
        if(dfs(0)){
            return "Win";
        }else{
            return "Lose";
        }
    }
};
DevuAndGame solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.canWin({1,-1}) << endl;
    cout << solver.canWin({1,0,-1}) << endl;
    cout << solver.canWin({0,1,2}) << endl;
    cout << solver.canWin({29,33,28,16,-1,11,10,14,6,31,7,35,34,8,15,17,26,12,13,22,1,20,2,21,-1,5,19,9,18,4,25,32,3,30,23,10,27}) << endl;
    cout << solver.canWin({17,43,20,41,42,15,18,35,-1,31,7,33,23,33,-1,-1,0,33,19,12,42,-1,-1,9,9,-1,39,-1,31,46,-1,20,44,41,-1,-1,12,-1,36,-1,-1,6,47,10,2,4,1,29}) << endl;
    cout << solver.canWin({3, 1, 1, 2, -1, 4}) << endl;
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
