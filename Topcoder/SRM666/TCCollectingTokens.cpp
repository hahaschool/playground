//
//  TCCollectingTokens.cpp
//  playground
//
//  Created by 張正昊 on 18/5/2016.
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

class CollectingTokens{
public:
    static const int MAXN = 55,MAXL = 105;
    int dp[MAXN][MAXL][MAXN][2];//dp[subtree root][assigned cost][fst e child][return x]
    int val[MAXN],mat[MAXN][MAXN],N;
    vector<int> son[MAXN];
    void dfs(int u,int par){
        for (int i = 1; i <= N; i++) {
            if(mat[u][i] && i != par){
                son[u].push_back(i);
                dfs(i, u);
            }
        }
    }
    int getd(int rt,int l,int e,int stay){
        if(dp[rt][l][e][stay] != -1) return dp[rt][l][e][stay];
        if(!e) return dp[rt][l][e][stay] = 0;
        //不进入新考虑的子树
        int ret = 0;
        if(!stay) ret = max(ret,getd(rt, l, e-1, 0));
        ret = max(ret,getd(rt, l, e-1, 1));
        if(!l) return ret;
        
        int cur = son[rt][e-1];//eth child
        //进了回
        for (int i = 0; i <= l-2; i++) {
            ret = max(ret,getd(rt,l-2-i,e-1,stay) +val[cur]+ getd(cur, i, son[cur].size(), 1));
        }
        if (!stay) {
            //进了不回
            for (int i = 0; i <= l-1; i++) {
                ret = max(ret,getd(rt,l-1-i, e-1, 1) +val[cur]+ getd(cur, i, son[cur].size(), 0));
                ret = max(ret,getd(rt,l-1-i, e-1, 1) +val[cur]+ getd(cur, i, son[cur].size(), 1));
            }
        }
        return dp[rt][l][e][stay] = ret;
    }
    
    int maxTokens(vector<int> A,vector<int> B,vector<int> tokens,int L){
        N = tokens.size();
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < A.size(); i++) {
            mat[A[i]][B[i]] = mat[B[i]][A[i]] = 1;
        }
        for (int i = 0; i < tokens.size(); i++) {
            val[i+1] = tokens[i];
            son[i+1].clear();
        }
        memset(dp, -1, sizeof(dp));
        dfs(1, -1);
        int res = 0;
        for (int i = 0; i <= son[1].size(); i++) {
            res = max(res,getd(1, L, i, false)+val[1]);
        }
        return res;
    }
    
};

CollectingTokens solver;

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    cout << solver.maxTokens({1}, {2}, {7,1}, 6) << endl;
    cout << solver.maxTokens({3,1},{2,2},{2,3,9},5) << endl;
    cout << solver.maxTokens({1,2,5,3},{4,4,1,4},{6,1,6,4,4},3) << endl;
    cout << solver.maxTokens({9,1,7,10,5,8,3,4,2},{6,6,9,6,6,1,1,6,6},{4,2,1,6,3,7,8,5,2,9},4) << endl;
    cout << solver.maxTokens({25,22,35,42,40,9,32,12,37,44,23,1,24,28,20,4,26,33,11,48,34,6,16,50,46,17,8,43,18,30,31,36,39,13,
        10,45,3,47,15,2,29,19,7,14,41,49,38,27,21},{5,5,25,25,25,42,25,40,5,35,25,32,42,9,32,23,40,25,20,33,26,37,12,1,48,24,22,25,11,24,48,34,18,9,50,42,16,40,1,
        10,47,22,48,44,48,1,4,46,47},{6,9,4,9,5,8,6,4,4,1,4,8,3,4,5,8,5,6,4,9,7,9,7,9,5,2,7,2,7,7,5,9,5,8,5,7,1,9,3,9,3,6,4,5,5,4,7,9,2,2},48) << endl;
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
