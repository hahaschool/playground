//
//  TCOneEntrance.cpp
//  playground
//
//  Created by 張正昊 on 20/5/2016.
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

class OneEntrance{
public:
    static const int MAXN = 15,MAXE = MAXN*2;
    int head[MAXN],nxt[MAXE],ed[MAXE],q;
    int n;
    void clear_gph(){
        q = 2;
        for (int i = 1;i <= n; i++) {
            head[i] = 0;
        }
    }
    void ade(int s,int t){
        ed[q] = t;
        nxt[q] = head[s];
        head[s] = q++;
    }
    
    int C[MAXN][MAXN];
    void prepare(){
        //binominal preprocessing
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if(j == 0) C[i][j] = 1;
                else if(j > i) C[i][j] = 0;
                else C[i][j] = C[i-1][j-1]+C[i-1][j];
            }
        }
    }
    int multinominal(int n,vector<int> k){
        int ret = 1;
        for (int i = 0; i < k.size(); i++) {
            ret = ret* C[n][k[i]];
            n -= k[i];
        }
        return ret;
    }

    int dp_siz[MAXN];
    int getSubtreeSize(int u,int par){
        if(dp_siz[u] != -1) return dp_siz[u];
        int ret = 1;
        for (int i = head[u]; i; i=nxt[i]) {
            int v = ed[i];
            if(v != par){
                ret += getSubtreeSize(v, u);
            }
        }
        return dp_siz[u] = ret;
    }
    int dp_single[MAXN];
    int getd_single(int u,int par){
        if(dp_single[u] != -1) return dp_single[u];
        int ret = 1;
        int usiz = getSubtreeSize(u, par);
        vector<int> veck;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if(v != par){
                veck.push_back(getSubtreeSize(v, u));
                ret = getd_single(v, u)*ret;
            }
        }
        ret = multinominal(usiz-1, veck)*ret;
        return dp_single[u] = ret;
    }
    
    int count(vector<int> a,vector<int> b,int s){
        n = a.size()+1;
        clear_gph();
        for (int i = 0; i < a.size(); i++) {
            ade(a[i]+1, b[i]+1);
            ade(b[i]+1, a[i]+1);
        }
        memset(dp_siz, -1, sizeof(dp_siz));
        memset(dp_single, -1, sizeof(dp_single));
        return getd_single(s+1, -1);
    }
    OneEntrance(){
        prepare();
    }
};

OneEntrance solver;

void commitTest(vector<int> a,vector<int> b,int s){
    cout << solver.count(a, b, s) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest({0,1,2}, {1,2,3},0);
    commitTest({0,1,2}, {1,2,3},2);
    commitTest({0,0,0,0},{1,2,3,4},0);
    commitTest({7, 4, 1, 0, 1, 1, 6, 0},{6, 6, 2, 5, 0, 3, 8, 4},4);
    commitTest({},{},0);
    
    
    
    
    
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
