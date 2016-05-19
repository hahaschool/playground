//
//  TCWalkOverATree.cpp
//  playground
//
//  Created by 張正昊 on 19/5/2016.
//  Copyright © 2016 Adam Chang. All rights reserved.
//

//A greedy-esque idea.

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

class WalkOverATree{
public:
    static const int MAXN = 55;
    int mat[MAXN][MAXN],n,dep[MAXN];
    void dfs(int u,int par,int _dep){
        dep[u] = _dep;
        for (int i = 1; i <= n; i++) {
            if(mat[u][i] && i != par){
                dfs(i, u, _dep+1);
            }
        }
    }
    int maxNodesVisited(vector<int> parent,int L){
        memset(mat, 0, sizeof(mat));
        n = parent.size()+1;
        for (int i = 0; i < parent.size(); i++) {
            mat[i+1][parent[i]] = mat[parent[i]][i+1] = 1;
        }
        dfs(0, -1, 0);
        int res = 0;
        for (int i = 1; i <= n; i++) {
            res = max(dep[i],res);
        }
        if (L <= res) {
            return L+1;
        }
        return min(n,res+1+(L-res)/2);
    }
};

WalkOverATree solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.maxNodesVisited({0,0}, 2) << endl;
    cout << solver.maxNodesVisited({0,0}, 3) << endl;
    cout << solver.maxNodesVisited({0,1,2,3}, 2) << endl;
    cout << solver.maxNodesVisited({0,0,0,0,2,4,2,3,1}, 1) << endl;
    cout << solver.maxNodesVisited({0,0,1,2,3,2,3,1,3,0,1,8,6,8,0,5,15,0,9}, 4) << endl;
    cout << solver.maxNodesVisited({0,0,0,1,1,3,5,1,4,5,2,2,10,5,10,10,11,13,8,3,18,15,20,20,23,8,11,26,4},26) << endl;
    cout << solver.maxNodesVisited({0, 0, 2, 0},100) << endl;
    cout << solver.maxNodesVisited({0, 0, 2},4) << endl;
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
