//
//  TCTwoEntrances.cpp
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

class TwoEntrances{
public:
    static const int MAXN = 3005,MAXE = MAXN*2;
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
    
    typedef long long LL;
    static const LL MODER = 1000000007;
    inline LL mod(LL a){
        if(a >= MODER || a < 0) a %= MODER;
        if(a < 0) a += MODER;
        return a;
    }
    LL sum_mod(LL a,LL b){
        return mod(mod(a)+mod(b));
    }
    LL mul_mod(LL a,LL b){
        return mod(mod(a)*mod(b));
    }
    
    LL C[MAXN][MAXN];
    void prepare(){
        //binominal preprocessing
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                if(j == 0) C[i][j] = 1;
                else if(j > i) C[i][j] = 0;
                else C[i][j] = sum_mod(C[i-1][j-1],C[i-1][j]);
            }
        }
    }
    LL multinominal(int n,vector<int> k){
        LL ret = 1;
        for (int i = 0; i < k.size(); i++) {
            ret = mul_mod(ret, C[n][k[i]]);
            n -= k[i];
        }
        return ret;
    }
    
    int mainChain[MAXN],chaintot;
    bool getMainChain(int u,int par,int tar){
        if (u == tar) {
            mainChain[++chaintot] = u;;
            return true;
        }
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if (v != par && getMainChain(v, u, tar)) {
                mainChain[++chaintot] = u;
                return true;
            }
        }
        return false;
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
    int chainSiz[MAXN],chainSizSum[MAXN];
    void prepareChainSize(){
        for (int i = 1; i <= chaintot; i++) {
            int u = mainChain[i];
            chainSiz[i] = 1;
            for (int j = head[u]; j; j = nxt[j]) {
                int v = ed[j];
                if(v != mainChain[i-1] && v != mainChain[i+1]){
                    chainSiz[i] += getSubtreeSize(v, u);
                }
            }
        }
        for (int i = 1; i <= chaintot; i++) {
            chainSizSum[i] = chainSizSum[i-1] + chainSiz[i];
        }
    }
    int getChainSize(int s,int t){
        return chainSizSum[t] - chainSizSum[s-1];
    }
    
    LL dp_double[MAXN][MAXN];
    LL getd_double(int s,int t){
        if(dp_double[s][t] != -1) return dp_double[s][t];
        LL ret = 1;
        vector<int> veck;
        if (s == t) {
            int u = mainChain[s];
            int sizu = getChainSize(s, s);
            for (int i = head[u]; i; i = nxt[i]) {
                int v = ed[i];
                if(v != mainChain[s-1] && v != mainChain[s+1]){
                    veck.push_back(getSubtreeSize(v, u));
                    ret = mul_mod(ret, getd_single(v, u));
                }
            }
            ret = mul_mod(multinominal(sizu-1, veck), ret);
        }else{
            //try s-<<<>>>
            LL reta = 1;
            int u = mainChain[s];
            veck.push_back(getChainSize(s+1, t));
            reta = mul_mod(getd_double(s+1, t), reta);
            int sizu = getChainSize(s, t);
            for (int i = head[u]; i; i = nxt[i]) {
                int v = ed[i];
                if(v != mainChain[s-1] && v != mainChain[s+1]){
                    veck.push_back(getSubtreeSize(v, u));
                    reta = mul_mod(reta, getd_single(v, u));
                }
            }
            reta = mul_mod(multinominal(sizu-1, veck), reta);
            //try <<<>>>-t
            LL retb = 1;
            u = mainChain[t];
            veck.clear();
            veck.push_back(getChainSize(s, t-1));
            retb = mul_mod(getd_double(s, t-1), retb);
            for (int i = head[u]; i; i = nxt[i]) {
                int v = ed[i];
                if(v != mainChain[t-1] && v != mainChain[t+1]){
                    veck.push_back(getSubtreeSize(v, u));
                    retb = mul_mod(retb, getd_single(v, u));
                }
            }
            retb = mul_mod(multinominal(sizu-1, veck), retb);
            ret = sum_mod(reta, retb);
        }
        return dp_double[s][t] = ret;
    }
    LL dp_single[MAXN];
    LL getd_single(int u,int par){
        if(dp_single[u] != -1) return dp_single[u];
        LL ret = 1;
        int usiz = getSubtreeSize(u, par);
        vector<int> veck;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = ed[i];
            if(v != par){
                veck.push_back(getSubtreeSize(v, u));
                ret = mul_mod(getd_single(v, u), ret);
            }
        }
        ret = mul_mod(multinominal(usiz-1, veck), ret);
        return dp_single[u] = ret;
    }
    
    int count(vector<int> a,vector<int> b,int s1,int s2){
        n = a.size()+1;
        clear_gph();
        for (int i = 0; i < a.size(); i++) {
            ade(a[i]+1, b[i]+1);
            ade(b[i]+1, a[i]+1);
        }
        memset(mainChain, -1, sizeof(mainChain));
        memset(dp_siz, -1, sizeof(dp_siz));
        memset(dp_single, -1, sizeof(dp_single));
        memset(dp_double, -1, sizeof(dp_double));
        chaintot = 0;
        getMainChain(s1+1, -1, s2+1);
        prepareChainSize();
        return getd_double(1, chaintot);
    }
    TwoEntrances(){
        prepare();
    }
};

TwoEntrances solver;
void commitTest(vector<int> a,vector<int> b,int s1,int s2){
    cout << solver.count(a, b, s1, s2) << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r", stdin);
    clock_t clk = clock();
#endif
    commitTest({0, 1, 2},{1, 2, 3},0,1);//4
    commitTest({0, 1, 2},{1, 2, 3},0,2);//9
    commitTest({0, 1, 1, 3, 3, 3, 6, 7, 6},{1, 2, 3, 4, 5, 6, 7, 8, 9},1,9);//16000
    commitTest({0, 0, 1, 2, 3, 1, 2, 0, 6, 5, 10, 10},{1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10, 11, 12},3,6);//310464
    commitTest({0},{1},1,0);//2
#ifndef ONLINE_JUDGE
    printf("Time Elapsed: %luMS\n",(clock() - clk)/CLK_TCK/10);
#endif
    
    return 0;
}
